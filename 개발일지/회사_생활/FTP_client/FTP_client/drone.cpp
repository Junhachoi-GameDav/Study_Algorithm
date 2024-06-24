#include "drone.h"

// std
#include <bit>
#include <chrono>
#include <format>
#include <filesystem>
#include <fstream>
#include <iosfwd>
#include <memory>
#include <regex>
#include <set>
#include <string>
#include <thread>
#include <vector>
#include <queue>
#include <ostream>

// boost
#include <boost/asio.hpp>

#include <cstdint>
// libTIFF
#include <tiffio.h>
#include <tiffio.hxx>

// this project
#include "processing.h"
//#include "../gps_image_io/gps_image_io.h"
//#include "../web_server/web_server_transfer.h"
#include "signal_receiver.h"
//#include "../global_logger.h"
#include "drone_db_connection.h"

// pqxx
#include <pqxx/pqxx>

std::atomic<unsigned int> drone::instances_count = 0U;

drone::drone(const configuration::config::_drone& d_con) : drone_config(d_con), file_get_mode(file_getter{ file_getter::handle_type() }), db_con(drone_db_connection())
{
	const unsigned int count = instances_count.load(std::memory_order::acquire);
	if (count == 0)
	{
		CURLcode result = curl_global_init(CURL_GLOBAL_DEFAULT);

		while (result != CURLcode::CURLE_OK)
			result = curl_global_init(CURL_GLOBAL_DEFAULT);
	}
	instances_count.fetch_add(1, std::memory_order::release);

	const auto path_check = [](const std::filesystem::path& path)->bool
	{
		return (!path.empty() && std::filesystem::exists(path));
	};

	/*if (path_check(drone_config.iop_eo_path))
		_iop_eo = iop(drone_config.iop_eo_path);

	if (path_check(drone_config.iop_ir_path))
		_iop_ir = iop(drone_config.iop_ir_path);

	if (path_check(drone_config.syscal_path))
		_syscal = syscal(drone_config.syscal_path);*/

	run();
}

drone::~drone()
{
	const unsigned int count = instances_count.load(std::memory_order::acquire);

	if (count == 1)
		curl_global_cleanup();

	instances_count.fetch_sub(1, std::memory_order::release);
}

bool drone::is_jpg_valid(const std::span<unsigned char>& image_binary_buffer)
{
	if (image_binary_buffer.size() < 4)
		return false;
	// jpg 파일은 맨 앞과 맨 뒤, 각각 2바이트가 SOI(Start of Image) / EOI(End of Image)라는 magic value 이며 각각 0xFF, 0xD8 0xFF, 0xD9 이다.
	// 맨 뒤 바이트가 EOI와 같은지 검사하여 이미지의 완전 전송 여부를 판단한다.
	// SOI는 혹시나 해서 검사하는거다.
	// 전송 순서가 뒤죽박죽이라면 사용하지 못할 수도 있다.(테스트 안해봄)
	const unsigned short soi = *static_cast<const unsigned short* const>(static_cast<const void* const>(&image_binary_buffer[0]));
	const unsigned short eoi = *static_cast<const unsigned short* const>(static_cast<const void* const>(&image_binary_buffer[image_binary_buffer.size() - 2]));

	if constexpr (std::endian::native == std::endian::little)
	{
		if (soi != 0xD8FF or eoi != 0xD9FF)
			return false;
	}
	else
	{
		if (soi != 0xFFD8 or eoi != 0xFFD9)
			return false;
	}

	return true;
}

bool drone::is_jpg_valid(const std::filesystem::path& image_abs_path)
{
	if (!std::filesystem::exists(image_abs_path))
		return false;
	
	auto jpg_binary = fast_file_read(image_abs_path);

	return is_jpg_valid(jpg_binary);
}

bool drone::is_tiff_valid(const std::span<unsigned char>& image_binary_buffer)
{
	std::istringstream iss(std::string(image_binary_buffer.begin(), image_binary_buffer.end()), std::ios::binary);

	TIFF* tif = TIFFStreamOpen("tiffmem", &iss);

	if (tif == nullptr)
		return false;
	
	TIFFClose(tif);
	return true;
}

bool drone::is_tiff_valid(const std::filesystem::path& image_abs_path)
{
	if (!std::filesystem::exists(image_abs_path))
		return false;
	
	auto tiff_binary = fast_file_read(image_abs_path);

	return is_tiff_valid(tiff_binary);
}

bool drone::is_done() const
{
	if (!waiting_task.valid())
		waiting_task = std::async(std::launch::async, [this]()->void
		{
			tg.wait();
			_is_done.store(true, std::memory_order::seq_cst);
		});

	const bool result = _is_done.load(std::memory_order::seq_cst);
	if (!result)
		return false;

	waiting_task = std::future<void>();
	_is_done.store(false, std::memory_order::seq_cst);
	return true;
}

void drone::run()
{
	const auto& [drone_key, address, port, id, pw, iop_eo_path, iop_ir_path, syscal_path] = drone_config;
	if (address.empty())
	{
		std::println("this drone is not gonna run, since it has empty address - invalid");
		return;
	}
	const auto is_ip_address = [](const std::string& address)->bool
	{
		static const std::regex ip_format("[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}", std::regex::optimize);
		return std::regex_match(address, ip_format);
	};

#if COROUTINE_MODE
	if (is_ip_address(address))
		file_get_mode = from_remote();
	else
		file_get_mode = from_local();
#else
	if (is_ip_address(address))
	{
		connect_to_gcs();
		connect_to_cam();
	}
	else
		get_local_file();
#endif
}
#pragma region get local file (안씀)
//bool drone::get_local_file()
//{
//	namespace fs = ::std::filesystem;
//	bool result = false;
//	const auto task_local_load = [this, &result]()->void
//	{
//		const auto& [drone_key, address, port, id, pw, iop_eo_path, iop_ir_path, syscal_path] = drone_config;
//		if (!fs::exists(address))
//		{
//			result = false;
//			return;
//		}
//
//		result = true;
//		for (const auto& file : fs::directory_iterator(address))
//			data_queue.push(file.path());
//	};
//	tg.run(task_local_load);
//
//	return result;
//}
#pragma endregion
#pragma region connect to cam (안씀)
//bool drone::connect_to_cam()
//{
//	namespace fs = ::std::filesystem;
//	const auto task_file_download = [this]()->void
//	{
//		const auto& [drone_key, address, port, id, pw, iop_eo_path, iop_ir_path, syscal_path] = drone_config;
//
//		std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl(curl_easy_init(), curl_easy_cleanup);
//		
//		// address
//		curl_easy_setopt(curl.get(), CURLOPT_URL, address.c_str());
//		
//		// account
//		curl_easy_setopt(curl.get(), CURLOPT_USERNAME, id.c_str());
//		curl_easy_setopt(curl.get(), CURLOPT_PASSWORD, pw.c_str());
//
//		// writing functor
//		const auto write_callback = [](void* contents, size_t size, size_t nmemb, std::string* userp)->size_t
//		{
//			userp->append((char*)contents, size * nmemb);
//			return size * nmemb;
//		};
//		curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_callback);
//
//		constexpr const char* remote_target_directory = "ssd";
//		const fs::path default_remote_directory = std::format("ftp://{}:{}/{}", address, port, remote_target_directory);
//		
//		// functors
//		const auto list_directory = [default_remote_directory](CURL* curl, const fs::path& sub_dir = fs::path())->std::vector<fs::path>
//		{
//			const std::string full_url = sub_dir.empty() ? default_remote_directory.generic_string() : (default_remote_directory / sub_dir).generic_string();
//			curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());
//
//			std::string data;
//			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
//			
//			// set DIRLISTONLY option to true
//			curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 1L);
//
//			while (true)
//			{
//				CURLcode res = curl_easy_perform(curl);
//				if (res == CURLcode::CURLE_OK)
//					break;
//
//				// error handling process...
//			}
//
//			// set DIRLISTONLY option to false
//			curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 0L);
//
//			std::istringstream iss(data);
//
//			std::vector<fs::path> entries;
//			std::string line;
//			while (std::getline(iss, line))
//			{
//				if (line == "." || line == "..")
//					continue;
//
//				entries.push_back(line);
//			}
//
//			std::sort(entries.begin(), entries.end());
//			
//			return entries;
//		};
//
//		const auto wait_until_file_is_not_writing = [default_remote_directory](CURL* curl, const fs::path& remote_path)->size_t
//		{
//			const std::string full_url = (default_remote_directory / remote_path).generic_string();
//
//			curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());
//			curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
//			curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
//
//			double file_size = 0.0;
//			while (true)
//			{
//				double new_file_size = 0.0;
//				CURLcode res = curl_easy_perform(curl);
//				if (res != CURLcode::CURLE_OK)
//				{
//					//...
//					continue;
//				}
//
//				curl_easy_getinfo(curl, CURLINFO::CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &new_file_size);
//				if (file_size == 0.0 || file_size != new_file_size)
//				{
//					file_size = new_file_size;
//					std::this_thread::sleep_for(std::chrono::milliseconds(100));
//					continue;
//				}
//
//				return static_cast<size_t>(file_size);
//			}
//		};
//
//		const auto download_file = [default_remote_directory](CURL* curl, const std::string& remote_path)->std::string
//		{
//			const std::string full_url = (default_remote_directory / remote_path).generic_string();
//
//			curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());
//			
//			std::string content;
//			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
//			
//			CURLcode res = curl_easy_perform(curl);
//			if (res != CURLcode::CURLE_OK)
//			{
//				//...
//			}
//
//			return content;
//		};
//
//		// wait until start signal has received
//		while (!start_of_acq)
//			std::this_thread::yield();
//
//		std::set<fs::path> download_completed_remote;
//		unsigned int eo_index = 0U;
//		unsigned int ir_index = 0U;
//		bool download_complete = false;
//		// 촬영 종료 및 파일 다운로드가 완료 될 때까지
//		while (!end_of_acq || !download_complete)
//		{
//			// List the main directory("/ssd")
//			const std::vector<fs::path> remote_subdirectories = list_directory(curl.get());
//			if (remote_subdirectories.empty())
//			{
//				std::this_thread::yield();
//				continue;
//			}
//
//			// Find the most recent directory(directories named including datetime)
//			const fs::path& most_recent_dir = *remote_subdirectories.rbegin();
//			
//			// List the target directory("/ssd/(most recent dir)")
//			const std::vector<fs::path> files = list_directory(curl.get(), most_recent_dir);
//			if (files.empty())
//			{
//				std::this_thread::yield();
//				continue;
//			}
//
//			// Loop the list of files and download sequentially
//			for (const auto& filename : files)
//			{
//				if (download_completed_remote.contains(filename))
//					continue;
//
//				const fs::path remote_absolute_path = most_recent_dir / filename;
//				
//				// 웹 서버에서 제공받은 flight key 이름의 폴더를 생성할 것임.
//				// 연결하지 않고 파일을 받게 된 경우 "None"를 사용.
//				//const std::string& flight_key = web_server_transfer::instance().get_flight_key();
//				//const fs::path flight_key_directory = flight_key.empty() ? "None" : flight_key;
//				
//				const fs::path local_absolute_dir = target_config.file_saving_directory /*/ flight_key_directory*/ / std::format("{}", drone_key);
//				if (!fs::exists(local_absolute_dir))
//					fs::create_directories(local_absolute_dir);
//				
//				fs::path local_file_name;
//				bool is_jpg = filename.extension() == ".jpg" || filename.extension() == ".jpeg";
//				bool is_tiff = filename.extension() == ".tif" || filename.extension() == ".tiff";
//
//				if (is_jpg)
//					local_file_name = std::format("{}_{}.jpg", drone_key, eo_index++);
//				if (is_tiff)
//					local_file_name = std::format("{}_{}.tiff", drone_key, ir_index++);
//				else
//					continue;
//
//				std::string content;
//				while (true)
//				{
//					const size_t file_size = wait_until_file_is_not_writing(curl.get(), remote_absolute_path);
//					content.reserve(file_size);
//					content = download_file(curl.get(), remote_absolute_path.string());
//
//					if (is_jpg && !is_jpg_valid(content))
//						continue;
//					if (is_tiff && !is_tiff_valid(content))
//						continue;
//					
//					break;
//				}
//				download_completed_remote.insert(filename);
//
//				std::ofstream(local_absolute_dir / local_file_name, std::ios::binary) << content;
//				
//				data_queue.push(local_absolute_dir / local_file_name);
//			}
//		}
//	};
//
//	const auto get_acq_signal = [this]()->void
//	{
//		while (true)
//		{
//			//if (/**/)
//			//	start_of_acq = true;
//			//if (/**/)
//			//	end_of_acq = true;
//			
//			// some condition to break and return
//			//if (/**/)
//			// break;
//			std::this_thread::yield();
//		}
//	};
//	tg.run(task_file_download);
//	tg.run(get_acq_signal);
//
//	return true;
//}
#pragma endregion
#pragma region from_local (안씀)
drone::file_getter drone::from_local()
{
	namespace fs = ::std::filesystem;
	const auto& [drone_key, address, port, id, pw, iop_eo_path, iop_ir_path, syscal_path] = drone_config;
	unsigned int eo_index = 0U;
	unsigned int ir_index = 0U;

	//const std::string& flight_key = web_server_transfer::instance().get_flight_key();
	//const fs::path flight_key_directory = flight_key.empty() ? "None" : flight_key;
	/*const fs::path local_abs_dir = target_config.file_saving_directory / flight_key_directory / std::format("{}", drone_key);
	if (!fs::exists(local_abs_dir))
	{
		fs::create_directories(local_abs_dir);
	}*/
	std::set<fs::path> downloaded;
	while (true)
	{
		for (const auto& file : fs::directory_iterator(fs::path(address) / "ssd/24-05-28_15-27/img"))
		{
			if (downloaded.contains(file.path()))
				continue;

			if (file.is_directory())
				continue;

			if (file.path().extension() != ".jpg" and file.path().extension() != ".tiff")
				continue;

			std::basic_ifstream<uint8_t> reader(file.path(), std::ios::binary);
			
			if (file.path().extension() == ".jpg")
			{
				const fs::path local_abs_filename( target_config.file_saving_directory / std::format("{}_{}.jpg", drone_key, eo_index++));
				std::basic_ofstream<uint8_t>(local_abs_filename, std::ios::binary) << reader.rdbuf();
				downloaded.emplace(file.path());
				
				co_yield local_abs_filename;
			}
			if (file.path().extension() == ".tiff")
			{
				const fs::path local_abs_filename( target_config.file_saving_directory / std::format("{}_{}.tiff", drone_key, ir_index++));
				std::basic_ofstream<uint8_t>(local_abs_filename, std::ios::binary) << reader.rdbuf();
				downloaded.emplace(file.path());

				co_yield local_abs_filename;
			}

			//co_yield file.path();
		}
		const auto& acquisition = signal_receiver::instance().acquisition_status.at(address);
		if (not acquisition)
		{
			std::cout << std::format("{} The acquisition has been ended and there's no more file to download...\n", address);
			signal_receiver::instance().remove_drone(address);
			break;
		}
	}
	co_return;
}
#pragma endregion

drone::file_getter drone::from_remote()
{
	namespace fs = ::std::filesystem;
	class __curl_obj
	{
		std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> ptr;
	public:
		//ctor
		__curl_obj(const decltype(drone_config)& d_config) : ptr(std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>(curl_easy_init(), curl_easy_cleanup))
		{
			const auto& [drone_key, address, port, id, pw, iop_eo_path, iop_ir_path, syscal_path] = d_config;
			// address
			curl_easy_setopt(ptr.get(), CURLOPT_URL, address.c_str());
			// account
			curl_easy_setopt(ptr.get(), CURLOPT_USERNAME, id.c_str());
			curl_easy_setopt(ptr.get(), CURLOPT_PASSWORD, pw.c_str());

			// 타임아웃 설정
			curl_easy_setopt(ptr.get(), CURLOPT_TIMEOUT, 10L); // 요청이 10초를 초과하면 타임아웃이 발생하여 요청이 중단
			curl_easy_setopt(ptr.get(), CURLOPT_CONNECTTIMEOUT, 15L); // 서버에 연결을 시도하는데 15초를 초과하면 타임아웃이 발생하여 연결 시도가 중단

			// 전송 속도가 일정 속도 이하로 유지되면 타임아웃
			curl_easy_setopt(ptr.get(), CURLOPT_LOW_SPEED_TIME, 10L); // 10초 동안
			curl_easy_setopt(ptr.get(), CURLOPT_LOW_SPEED_LIMIT, 1250L); // 1,250 바이트/초 (10 kb/s) 이하로 유지되면 타임아웃
		}

		// no copy and move
		__curl_obj(const __curl_obj&) = delete;
		__curl_obj& operator=(const __curl_obj&) = delete;
		__curl_obj(__curl_obj&&) = delete;
		__curl_obj& operator=(__curl_obj&&) = delete;

		// dtor
		~__curl_obj() = default;

		// pointer casting 
		operator CURL* () const & noexcept { return ptr.get(); }
	} curl(drone_config);

	const auto& [drone_key, address, port, id, pw, iop_eo_path, iop_ir_path, syscal_path] = drone_config;
	
	//// writing functor
	//// 람다 앞에 +가 붙어있으면 함수 객체 대신 함수 포인터로 컴파일해준다
	//// 대신 캡쳐에 뭐가 들어있으면 안된다
	//// 이 요망한 C 라이브러리 cURL은 함수 객체 같은건 모르기 때문에 함수 포인터로 변환해준다
	//// 그냥 람다로 넣으면 터진다
	//const auto write_callback_string = +[](char* contents, size_t size, size_t nmemb, std::string* userp)->size_t
	//{
	//	assert(userp != nullptr);
	//	userp->append(static_cast<std::remove_cvref_t<decltype(*userp)>::pointer>(static_cast<void*>(contents)), size * nmemb);
	//	
	//	return size * nmemb;
	//};
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &remote::write_callback_string<std::string>);

#pragma region 전에 것

	// 디렉토리 조회(조회 후 이름 오름차순으로 정렬함)
	// 조회 결과가 CURLcode::CURLE_OK가 아니면(네트워크 환경, 잘못된 경로, 기타...) 빈 목록을 반환함.
	//const auto list_directory = [write_callback_string](CURL* curl, const fs::path& remote_path)->std::vector<fs::path>
	//{
	//	assert(curl != nullptr);
	//	assert(not remote_path.empty());
	//
	//	// 디렉토리 조회 시 경로 마지막에 /가 붙어야 한다.
	//	curl_easy_setopt(curl, CURLOPT_URL, (remote_path.generic_string() + "/").c_str());
	//
	//	std::string data;
	//	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
	//	class __dirlist_only
	//	{
	//		CURL* curl;
	//	public:
	//		__dirlist_only(CURL* c) : curl(c)
	//		{
	//			// set DIRLISTONLY option to true
	//			curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 1L);
	//		}
	//		~__dirlist_only()
	//		{
	//			// set DIRLISTONLY option to false after the operation has done
	//			curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 0L);
	//		}
	//	} dirlist_only(curl);
	//
	//	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_string);
	//
	//	CURLcode res = curl_easy_perform(curl);
	//	if (res != CURLcode::CURLE_OK)
	//		return {};
	//
	//	std::istringstream iss(data);
	//
	//	std::vector<fs::path> entries;
	//	std::string line;
	//	while (std::getline(iss, line))
	//	{
	//		std::erase(line, '\r');
	//		std::u8string convertedu8(line.begin(), line.end());
	//
	//		if (line == "." || line == "..")
	//			continue;
	//		
	//		entries.push_back(convertedu8);
	//	}
	//
	//	std::sort(entries.begin(), entries.end());
	//
	//	return entries;
	//};

	// 파일이 쓰기 되지 않을 때까지 대기(사이즈 검사를 반복하여 이전의 결과와 같은 크기이면 쓰기가 완료되었다고 판단)
	// 지속적으로 사이즈를 조회하는 도중 조회 결과가 CURLcode::CURLE_OK가 아니면 0을 반환함.
	//const auto wait_until_file_is_not_writing = [](CURL* curl, const fs::path& remote_path)->size_t
	//{
	//	assert(curl != nullptr);
	//	assert(not remote_path.empty());
	//
	//	// 파일 주소 설정
	//	curl_easy_setopt(curl, CURLOPT_URL, remote_path.generic_string().c_str());
	//
	//	// 파일을 불러오는 것이 아니라 파일 헤더만 가져옴(사이즈만 구하기 위함)
	//	class __header_only
	//	{
	//		CURL* ptr;
	//	public:
	//		__header_only(CURL* curl) : ptr(curl)
	//		{
	//			curl_easy_setopt(ptr, CURLOPT_NOBODY, 1L);
	//			curl_easy_setopt(ptr, CURLOPT_HEADER, 1L);
	//		}
	//
	//		~__header_only()
	//		{
	//			curl_easy_setopt(ptr, CURLOPT_NOBODY, 0L);
	//			curl_easy_setopt(ptr, CURLOPT_HEADER, 0L);
	//		}
	//	} header_only(curl);
	//
	//	// 실제로는 콜백도 호출되고 스트링 형태로 오는 데이터가 있지만 밑에서 CURLINFO::CURLINFO_CONTENT_LENGTH_DOWNLOAD_T 태그로
	//	// curl_easy_getinfo를 하면 사이즈를 얻을 수 있기 때문에 굳이 스트링 파싱을 직접 할 필요는 없다.
	//	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](char* contents, size_t size, size_t nmemb, void* userp)->size_t
	//	{
	//		return size * nmemb;
	//	});
	//	
	//	// 파일 사이즈 1회 호출하는 람다 정의
	//	const auto get_file_size = [&curl]()->size_t
	//	{
	//		size_t size;
	//		CURLcode res = curl_easy_perform(curl);
	//		
	//		// 파일 사이즈 받기에 실패한 경우 0 반환
	//		if (res != CURLcode::CURLE_OK)
	//			return 0ULL;
	//		
	//		curl_easy_getinfo(curl, CURLINFO::CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &size);
	//		return size;
	//	};
	//
	//	size_t sz0 = get_file_size();
	//	if (sz0 == 0ULL)
	//		return 0ULL;
	//	
	//	while (true)
	//	{
	//		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	//		const size_t sz1 = get_file_size();
	//		
	//		if (sz1 == 0ULL)
	//			return 0ULL;
	//		
	//		if (sz1 != sz0)
	//		{
	//			sz0 = sz1;
	//			continue;
	//		}
	//
	//		return sz1;
	//	}
	//};
	
	// 파일 다운로드(파일이 담긴 바이너리 스트링을 반환)
	// 다운로드 결과가 CURLcode::CURLE_OK가 아니면 빈 문자열을 반환함.
	//const auto download_file = [](CURL* curl, const fs::path& remote_path, size_t reserve_size_hint = 0ULL)->std::basic_string<uint8_t>
	//{
	//	assert(curl != nullptr);
	//	assert(not remote_path.empty());
	//
	//	const std::string full_url = remote_path.generic_string();
	//
	//	curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());
	//
	//	std::basic_string<uint8_t> content;
	//	if (reserve_size_hint != 0ULL)
	//		content.reserve(reserve_size_hint);
	//
	//	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
	//
	//	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](char* contents, size_t size, size_t nmemb, std::basic_string<uint8_t>* userp)->size_t
	//	{
	//		userp->append(static_cast<std::remove_cvref_t<decltype(*userp)>::pointer>(static_cast<void*>(contents)), size * nmemb);
	//
	//		return size * nmemb;
	//	});
	//
	//	CURLcode res = curl_easy_perform(curl);
	//	if (res != CURLcode::CURLE_OK)
	//		return {};
	//
	//	return content;
	//};

	// Wiris Enterprise의 디렉토리 구조
	// /{storage}/{yy}-{MM}-{dd}_{hh}-{mm}/{acquisition_type}/{hh}-{mm}-{ss}-{ms}-{option}.{extension}
	// 
	// {storage}								: 저장소, flashd, sdcard, ssd가 있다. 기본적으로 ssd에 촬영 파일이 쓰여지고 flashd, sdcard는 옮길 때 쓰인다.
	// {yy}-{MM}-{dd}_{hh}-{mm}					: 부팅한 시간(분 단위)으로 명명된 폴더가 만들어진다.
	// 재부팅 하기 전까지의 모든 촬영 파일이 이 폴더 내에 있다.
	// {acquisition_type}						: 촬영 타입의 폴더가 생성된다, 사진이면 img, 동영상이면 vid이다.
	// {hh}-{mm}-{ss}-{ms}-{option}.{extension}	: 실제 촬영된 시간(밀리초 단위) 및 옵션을 이름으로 하는 파일이 생성된다.
	// 
	// Ex)
	// /ssd/24-03-29_14-16/img/14-18-52-995-highRes.jpg			(14시 16분 xx초 부팅 후 14시 18분 52.995초에 촬영된 고해상도 EO 카메라)
	// /ssd/24-03-29_14-16/img/14-18-52-995-radiometric.tiff	(14시 16분 xx초 부팅 후 14시 18분 52.995초에 촬영된 tiff 확장자의 IR카메라)
	// 
	// WARNING
	// 1. 촬영 데이터가 없는 디렉토리는 재부팅 시점에 삭제된다.
	// 2. 11시 59분에 부팅하여 디렉토리를 생성 후 12시에 촬영 시 다른 디렉토리가 만들어지는지 확인하지 않았다.
	// 3. 2일 이상 촬영시 Overwrite 되는지 확인하지 않았다.

#pragma endregion

#define V2
#ifdef V2
	
	unsigned int eo_index = 0;
	unsigned int ir_index = 0;
	
	// 로딩용 막대기
	std::vector<char> spinner = { '|', '/', '-', '/' };
	size_t spinner_index = 0;

	//// 시간 변수
	//bool work_done = false;
	//std::chrono::steady_clock::time_point start_time;
	//std::chrono::steady_clock::time_point end_time;

	// 가장 최근 폴더를 현재 촬영 중인 데이터 디렉토리로 가정하고 진행
	//const auto& most_recent_dir = remote::find_target_directory(curl, db_con, address, port);
	//위리스 카메라 기준 - 촬영시작되면 폴더가 생기고 
	const std::filesystem::path default_remote_directory = std::format("ftp://{}:{}/ssd", address, port);
	std::println("default_remote_directory = {}", default_remote_directory.string());

	while (true)
	{
		// 이미지 목록 조회
		auto files = remote::list_directory(curl, default_remote_directory);

		//file_get_mode.handle.promise().test_size = files.size();
		// 이미 다운로드 한 이미지 필터링(다운로드가 완료되면 DB에 경로가 INSERT 됨)
		std::erase_if(files, [this, &default_remote_directory](const fs::path& filename)->bool
		{
			std::string where_clause = std::format("remote_dir = '{}' AND remote_filename = '{}'", default_remote_directory.generic_string(), filename.generic_string());
			const auto select_result = db_con.select_query_file_index(where_clause);
	
			return not select_result.empty();
		});
		
		//////시작 시간을 잰 뒤 신호 못받으면 종료
		//if (!work_done)
		//{
		//	start_time = std::chrono::steady_clock::now();
		//	end_time = start_time + std::chrono::seconds(10); //임시 10초
		//}

		// 다운로드 할 것 다시 확인 및 종료
		if (files.empty())
		{
			// 촬영 시작-종료 신호 받기
			const auto& acquisition = signal_receiver::instance().acquisition_status.at(address);
			if (not acquisition)
			{
				std::println("\n{}:{} The acquisition has been ended and there's no more file to download. closing the FTP...", address, port);
				signal_receiver::instance().remove_drone(address);
				break; //종료
			}

			//work_done = true; //작업완료
			////다운이 완료된 뒤에 종료 or 신호 못받아도 작업완료되면 특정시간 뒤 종료
			//if (std::chrono::steady_clock::now() >= end_time || acquisition)
			//	break; //종료

			std::cout << std::format("\r{}:{} Waiting to download files {}", address, port, spinner[spinner_index]) << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(500)); //0.5초씩 FTP 재접속용
			spinner_index = (spinner_index + 1) % spinner.size();
			continue;
		}
		//else
		//	work_done = false; //작업중
		std::println("files_cnt = {} ", files.size());

		//이어서 받기
		//eo_index = had_file_idx;
		//ir_index = had_file_idx;

		// 오류시 다음이미지로 넘어가지 않게 하기
		for (const auto& target : files)
		{
			//// 파일 쓰기가 끝날 때까지 대기 후 파일 사이즈 가져옴
			WAITING_RETRY:
			const size_t file_size = remote::wait_until_file_is_not_writing(curl, default_remote_directory / target);
			if (file_size == 0ULL)
			{
				std::println("Can't read file_size ... Check Network connection......");
				goto WAITING_RETRY;
			}
			std::println("file_size = {}", file_size);

			// 다운로드 시도
			DOWNLOAD_RETRY:
			std::basic_string<uint8_t> content = remote::download_file(curl, default_remote_directory / target, 0);
			if (content.size() < file_size)
			{
				std::println("File download is failed ... must bigger ther content ... its wrong data ... Please Check Network connections...\n");
				goto DOWNLOAD_RETRY;
			}
			std::println("get content's Number = {}", eo_index + ir_index);

			// 웹 서버에서 제공받은 flight key 이름의 폴더를 생성할 것임.
			// 연결하지 않고 파일을 받게 된 경우 "None"를 사용.
			//const std::string& flight_key = web_server_transfer::instance().get_flight_key();
			//const fs::path flight_key_directory = flight_key.empty() ? "None" : flight_key;
	
			const fs::path local_abs_dir = target_config.file_saving_directory /*flight_key_directory*/ / std::format("{}", drone_key);
			if (!fs::exists(local_abs_dir)) //경로 생성 후 & db에 넣기
			{
				std::println("file is not exist ...... make dir at {} ..and insert DB.", local_abs_dir.string());
				fs::create_directories(local_abs_dir);
				db_con.insert_query_directory(0, default_remote_directory, local_abs_dir);
			}
	
			// 각 파일 타당성 검증
			const std::set<std::string> jpg_extensions{ ".jpg", ".jpeg" };
			const std::set<std::string> tiff_extensions{ ".tif", ".tiff" };
	
			if (jpg_extensions.contains(target.extension().generic_string()) /*and is_jpg_valid(content)*/)
			{
				// .jpg는 시작과 끝의 2바이트가 각각 SOI(Start of Image), EOI(End of Image)라는 magic value이고 각각 0xFFD8, 0xFFD9로 고정인데
				// Wiris Enterprise의 .jpg는 4바이트 단위로 끊어서 저장하는 것을 발견했다.
				// 예를 들어 실제 파일 사이즈가 999,997 바이트이면 1,000,000 바이트로 저장하고 뒤가 '\0'으로 채워진다.
				// 1바이트 기준 실제 EOI의 인덱스는 buffer[999995], buffer[999996]이지만 EOI 검사는 buffer[999998], buffer[999999]를 검사하므로
				// 0x0000을 읽게 되고, 정상적이지 않은 파일로 인식하여 다운로드하지 않는 문제가 발생했다.
				// 그러므로 뒤에서부터 널 문자('\0')를 지워서 파일 크기를 맞추고 EOI 검사를 실행한다.
				for (size_t i = content.size() - 1ULL; content.size() > 0 && content[i] == '\0'; --i)
					content.pop_back();
	
				if (not is_jpg_valid(content))
				{
					std::println("content is not jpg.......");
					continue;
				}

				const fs::path local_abs_filename(local_abs_dir / std::format("{}_{}.jpg", drone_key, eo_index++));
				std::basic_ofstream<uint8_t>(local_abs_filename, std::ios::binary) << content;

				db_con.insert_query_file_index(default_remote_directory / target, local_abs_filename);

				//다음 이미지
				co_yield local_abs_filename;
			}
			else if (tiff_extensions.contains(target.extension().generic_string()) and is_tiff_valid(content))
			{
				const fs::path local_abs_filename(local_abs_dir / std::format("{}_{}.tiff", drone_key, ir_index++));
				std::basic_ofstream<uint8_t>(local_abs_filename, std::ios::binary) << content;
	
				db_con.insert_query_file_index(default_remote_directory / target, local_abs_filename);
	
				//다음 이미지
				co_yield local_abs_filename;
			}
			//else
			//	continue;
		}
	}

	co_return;
#else
	const fs::path default_remote_directory = std::format("ftp://{}:{}/ssd", address, port);
	
	unsigned int eo_index = 0;
	unsigned int ir_index = 0;
	// 가장 최근 폴더를 현재 촬영 중인 데이터 디렉토리로 가정하고 진행
	remote::find_target_directory(curl, db_con, address, port);
	// ssd 디렉토리 검색
	std::vector<fs::path> list_dir_ssd;
	do
	{
		list_dir_ssd = remote::list_directory(curl, default_remote_directory);
		if (list_dir_ssd.empty())
		{
			logger::log("{}:{} cannot list default directory of drone.\ncould be either camera is off or network issue\nretry...\n", address, port);
			continue;
		}
	
		// 경로 타당성 확인
		std::erase_if(list_dir_ssd, [&default_remote_directory](const fs::path& path)->bool
		{
			if (path.empty())
				return true;

			const std::string directory_string = path.generic_string();

			// 날짜 및 시간 포맷("yy-MM-dd_hh-mm") 이름이 아닌 디렉토리 필터링
			if (not std::regex_match(directory_string, std::regex("[0-9]{2}-[0-9]{2}-[0-9]{2}_[0-9]{2}-[0-9]{2}", std::regex::optimize)))
				return true;

			// 1970년 1월 1일자로 생성된 디렉토리 필터링(가끔 부팅 중에 빠르게 접속하는 경우 디렉토리 명이 변경되지 않아 이런 디렉토리 검색됨)
			if (directory_string.substr(0, 8) == "70-01-01")
				return true;
			
			return false;
		});

		// 가장 최근 시간의 디렉토리를 제외한 디렉토리 대상에서 제외
		const fs::path recent_dir = *list_dir_ssd.rbegin();
		std::erase_if(list_dir_ssd, [&recent_dir](const fs::path& path)->bool
		{
			return path.generic_string() < recent_dir.generic_string();
		});

		// DB에 질의하여 해당 디렉토리가 있는지 검색
		std::erase_if(list_dir_ssd, [this, &default_remote_directory](const fs::path& path)->bool
		{
			// 이미 있는 디렉토리면 기존에 다운로드 받았던 경로이므로 대상 아님
			const auto select_directory_result =
				db_con.select_query_directory(std::format("remote_dir = '{}'", (default_remote_directory / path / "img").generic_string()));
			
			return not select_directory_result.empty();
		});
	} while (list_dir_ssd.empty());
	
	// 시간 제한 이후에는 종료
	constexpr std::chrono::milliseconds time_limit(10'000);
	namespace t = ::std::chrono;
	
	constexpr auto now = &std::chrono::system_clock::now;
	
	auto time_ends_at = now() + time_limit;
	for (auto timestamp = now(); timestamp < time_ends_at; timestamp = now())
	{
		// 가장 최근 시간대 이미지가 이번 부팅의 디렉토리일 것이므로 조회
		const auto& most_recent_dir = (*list_dir_ssd.rbegin()) / "img";
		
		// 이미지 목록 조회
		auto files = remote::list_directory(curl, default_remote_directory / most_recent_dir);
		
		// 이미 다운로드 한 이미지 필터링
		std::erase_if(files, [this, &default_remote_directory, &most_recent_dir](const fs::path& filename)->bool
		{
			std::string where_clause = std::format("remote_dir = '{}' AND remote_filename = '{}'", (default_remote_directory / most_recent_dir).generic_string(), filename.generic_string());
			const auto select_result = db_con.select_query_file_index(where_clause);
			
			return not select_result.empty();
		});

		// 더 다운로드 할 것이 없으면 time_limit만큼 대기 후 리턴(end를 알 수 없기 때문)
		if (files.empty())
		{
			const auto& acquisition = signal_receiver::instance().acquisition_status.at(address);
			if (not acquisition)
			{
				signal_receiver::instance().remove_drone(address);
				break;
			}

			// 다운로드 된 것이 있는지 확인
			const auto select_result = db_con.select_query_file_index(std::format("(remote_dir = '{}')", (default_remote_directory / most_recent_dir).generic_string()));
			
			if (select_result.empty())
			{
				// 다운로드 한 것이 없으면 아직 촬영 전, 시간 제한 늘림
				logger::log("{}:{} Acquisition has not been started. waiting...\n", address, port);
				time_ends_at = now() + time_limit;
			}
			else
			{
				// 촬영 시작된 이후에는 타임아웃 적용
				const float remaining_time = static_cast<float>(t::duration_cast<t::milliseconds>(time_ends_at - timestamp).count()) * 1e-3;
				logger::log("{}:{} have no new files. waiting for {:.3f} seconds and will be closed.\n", address, port, remaining_time);
			}
			continue;
		}

		for (const auto& target : files)
		{
			// 파일 쓰기가 끝날 때까지 대기 후 파일 사이즈 가져옴
			const size_t file_size = remote::wait_until_file_is_not_writing(curl, default_remote_directory / most_recent_dir / target);
			if (file_size == 0ULL)
				continue;

			// 다운로드 시도
			std::basic_string<uint8_t> content = remote::download_file(curl, default_remote_directory / most_recent_dir / target, file_size);
			if (content.size() < file_size)
				continue;

			// 웹 서버에서 제공받은 flight key 이름의 폴더를 생성할 것임.
			// 연결하지 않고 파일을 받게 된 경우 "None"를 사용.
			const std::string& flight_key = web_server_transfer::instance().get_flight_key();
			const fs::path flight_key_directory = flight_key.empty() ? "None" : flight_key;

			const fs::path local_abs_dir = target_config.file_saving_directory / flight_key_directory / std::format("{}", drone_key);
			if (!fs::exists(local_abs_dir))
			{
				fs::create_directories(local_abs_dir);
				db_con.insert_query_directory(0, default_remote_directory / most_recent_dir, local_abs_dir);
			}

			// 각 파일 타당성 검증
			const std::set<std::string> jpg_extensions{ ".jpg", ".jpeg" };
			const std::set<std::string> tiff_extensions{ ".tif", ".tiff" };
			
			if (jpg_extensions.contains(target.extension().generic_string()) /*and is_jpg_valid(content)*/)
			{
				// .jpg는 시작과 끝의 2바이트가 각각 SOI(Start of Image), EOI(End of Image)라는 magic value이고 각각 0xFFD8, 0xFFD9로 고정인데
				// Wiris Enterprise의 .jpg는 4바이트 단위로 끊어서 저장하는 것을 발견했다.
				// 예를 들어 실제 파일 사이즈가 999,997 바이트이면 1,000,000 바이트로 저장하고 뒤가 '\0'으로 채워진다.
				// 1바이트 기준 실제 EOI의 인덱스는 buffer[999995], buffer[999996]이지만 EOI 검사는 buffer[999998], buffer[999999]를 검사하므로
				// 0x0000을 읽게 되고, 정상적이지 않은 파일로 인식하여 다운로드하지 않는 문제가 발생했다.
				// 그러므로 뒤에서부터 널 문자('\0')를 지워서 파일 크기를 맞추고 EOI 검사를 실행한다.
				for (size_t i = content.size() - 1ULL; content[i] == '\0'; --i)
					content.pop_back();
				
				if (not is_jpg_valid(content))
					continue;

				const fs::path local_abs_filename(local_abs_dir / std::format("{}_{}.jpg", drone_key, eo_index++));
				std::basic_ofstream<uint8_t>(local_abs_filename, std::ios::binary) << content;
				
				db_con.insert_query_file_index(default_remote_directory / most_recent_dir / target, local_abs_filename);
				
				co_yield local_abs_filename;
			}
			else if (tiff_extensions.contains(target.extension().generic_string()) and is_tiff_valid(content))
			{
				const fs::path local_abs_filename(local_abs_dir / std::format("{}_{}.tiff", drone_key, ir_index++));
				std::basic_ofstream<uint8_t>(local_abs_filename, std::ios::binary) << content;

				db_con.insert_query_file_index(default_remote_directory / most_recent_dir / target, local_abs_filename);
				
				co_yield local_abs_filename;
			}
			else
				continue;
			
			// 시간 제한 늘림
			time_ends_at = now() + time_limit;
		}
	}
	co_return;
#endif
}
