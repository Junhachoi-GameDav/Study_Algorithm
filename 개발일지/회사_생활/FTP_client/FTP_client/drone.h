#pragma once

// std
#include <atomic>
#include <filesystem>
#include <future>
#include <span>
#include <coroutine>
#include <print>

// oneTBB
#include <oneapi/tbb/task_group.h>
#include <oneapi/tbb/concurrent_queue.h>

// libcURL
// NOMINMAX를 정의하지 않으면 네트워크를 지원하는 라이브러리의 Windows implementation 내에서 WinSock2.h를 포함하게 되고 이 헤더는 다시 minwindef.h를 포함하는데
// minwindef.h에서 #define min, #define max 매크로를 정의하면서 이 매크로가 std::min, std::max 및 온갖 최대, 최소 키워드에 들러붙어 에러가 뻥뻥 터진다.
// 마소 이 새끼들은 좀 이런거 안 고치나? 아님 지들만 아는 씹덕 키워드를 쓰던가. 이게 뭐냐고
#define NOMINMAX
#include <curl/curl.h>


// this project
//#include "../orientation_parameters/iop.hpp"
//#include "../orientation_parameters/eop.hpp"
#include "build_config.h"
#include "drone_db_connection.h"

#define COROUTINE_MODE true
/** drone
* 드론에 대응하는 클래스, 드론 1대당 하나의 인스턴스
* 인스턴스 개수를 세는 이유는 파일 전송을 위한 cURL 라이브러리가 global init을 요구하기 때문, 생성자 및 소멸자에서 각각 +1, -1 된다.
* 인스턴스 개수가 1 이상이 되면 init(1회) 하고 0이 되면 deinit 한다.
* 
* drone_config에서 주소를 읽어 주소가 IPv4 형식이면 드론 매핑, 그렇지 않으면 파일 매핑이다.
* 드론 매핑은 카메라에 할당된 IP 주소로 접속하여 이미지를 다운로드 받아 매핑한다.
* 파일 매핑은 디렉토리 경로로 인식하여 폴더 내의 이미지를 조사한다.
* 두 방식 모두 이미지 내에 메타데이터가 존재해야 한다.
* 
* 현재 자세값을 메타데이터로 넣을 수 없으므로 자세값을 받는 방법 및 자세값과 이미지의 동기화 방법을 고민해야 한다.
*/
class drone
{
	static std::atomic<unsigned int> instances_count;

	mutable tbb::task_group tg;
	mutable std::future<void> waiting_task;
	mutable std::atomic<bool> _is_done;

	bool start_of_acq;
	bool end_of_acq;

	// from configuration::config::_drone

	drone_db_connection db_con;

	// no default ctor
	drone() = delete;

public:
	const configuration::config::_drone& drone_config;

	//iop _iop_eo = iop("not-calibrated");
	//iop _iop_ir = iop("not-calibrated");
	//syscal _syscal = syscal("not-calibrated");

	tbb::concurrent_queue<std::filesystem::path> data_queue;

	// ctor
	drone(const configuration::config::_drone& d_con);
	
	// dtor
	~drone();

	// copyable and movable
	drone(const drone&) = default;
	drone& operator=(const drone&) = default;
	drone(drone&&) = default;
	drone& operator=(drone&&) = default;
	
	
	/// is_jpg_valid()
	/**
	 * jpg 바이너리가 온전한지 확인하는 함수.
	 * 모든 jpg 이미지는 start of image(SOI), end of image(EOI) 마커가 있다. 
	 * SOI는 .jpg 최전방 2바이트를 읽어 0xFFD8인지 검사한다(little endian 기준, be의 경우 0xD8FF) 
	 * EOI는 .jpg 최후방 2바이트를 읽어 0xFFD9인지 검사한다(little endian 기준, be의 경우 0xD9FF)
	 * std::filesystem::path를 받는 오버로드는 파일을 바이너리로 읽은 후 바이너리 형식의 오버로드를 호출한다.
	 * unsigned char 형식의 span이 아니면 path 타입의 오버로드를 호출할 수 있으므로 주의
	 * 
	 * @param image_binary_buffer .jpg 바이너리를 담은 버퍼
	 * 
	 * @return .jpg 바이너리가 온전한 경우 true, 아니면 false
	 */
	static bool is_jpg_valid(const std::span<unsigned char>& image_binary_buffer);

	static bool is_jpg_valid(const std::filesystem::path& image_abs_path);


	/// is_tiff_valid()
	/**
	* tiff 바이너리가 온전한 지 확인하는 함수, 검증되지 않았다.
	* 단지 TIFF* 형식으로 열어보아 nullptr가 뜨는지 아닌지만 검사한다.
	* nullptr가 아니지만 사실은 정상이 아닌 경우가 발견되면 코드는 수정되어야 한다.
	* std::filesystem::path를 받는 오버로드는 파일을 바이너리로 읽은 후 바이너리 형식의 오버로드를 호출한다.
	* unsigned char 형식의 span이 아니면 path 타입의 오버로드를 호출할 수 있으므로 주의
	* 
	* @param image_binary_buffer .tiff 바이너리를 담은 버퍼
	* 
	* @return .tiff 바이너리가 온전한 경우 true, 아니면 false
	*/
	static bool is_tiff_valid(const std::span<unsigned char>& image_binary_buffer);

	static bool is_tiff_valid(const std::filesystem::path& image_abs_path);

	// connect to camera
	void run();
	bool is_done() const;
	//bool get_local_file();
	//bool connect_to_cam();
	
	// coroutines
	class file_getter
	{
	public:
		struct promise_type
		{
			std::filesystem::path value;
			int test_size;

			file_getter get_return_object() noexcept { return file_getter{ std::coroutine_handle<promise_type>::from_promise(*this) }; }
			auto initial_suspend() const noexcept { return std::suspend_always{}; }
			auto final_suspend() const noexcept { return std::suspend_always{}; }
			auto yield_value(const std::filesystem::path& image_path) noexcept
			{
				value = image_path;
				return std::suspend_always{};
			}
			void return_void() const noexcept {};
			void unhandled_exception() {};
		};
		using handle_type = std::coroutine_handle<promise_type>;

		explicit file_getter(handle_type h) : handle(h) {}

		// non-copyable
		file_getter(const file_getter& t) noexcept = delete;
		file_getter& operator=(const file_getter& other) noexcept = delete;

		// movable
		file_getter(file_getter&& other) noexcept
		{
			std::swap(handle, other.handle);
		}
		file_getter& operator=(file_getter&& other) noexcept
		{
			std::swap(handle, other.handle);
			return *this;
		}
		~file_getter()
		{
			if (handle)
				handle.destroy();
		}

		void resume() const { handle.resume(); }
		bool done() const noexcept { return handle.done(); }

		std::coroutine_handle<promise_type> handle;
	};

	file_getter file_get_mode;
	file_getter from_local();
	file_getter from_remote(); //실 사용 ftp

	struct remote
	{
		//from_remote 내부에서 사용하는 정적 함수를 모아둔 클래스
		static inline size_t write_callback_noop(char* contents, size_t size, size_t nmemb, void* userp)
		{
			return size * nmemb;
		}
		template<typename _Ty> requires std::is_same_v<_Ty, std::basic_string<typename _Ty::value_type>>
		static inline size_t write_callback_string(char* contents, size_t size, size_t nmemb, _Ty* userp)
		{
			assert(userp != nullptr);
			userp->append(static_cast<std::remove_cvref_t<decltype(*userp)>::pointer>(static_cast<void*>(contents)), size * nmemb);

			return size * nmemb;
		};

		// WE 카메라 내 가장 최근 시간 대의(촬영분으로 예상되는) 디렉토리명 검색
		static std::filesystem::path find_target_directory(CURL* curl, drone_db_connection& db_con, const std::string& adress, const int port);

		// 디렉토리 조회(조회 후 이름 오름차순으로 정렬함)
		// 조회 결과가 CURLcode::CURLE_OK가 아니면(네트워크 환경, 잘못된 경로, 기타...) 빈 목록을 반환함.
		static std::vector<std::filesystem::path> list_directory(CURL* curl, const std::filesystem::path& remote_path);
		
		// 파일이 쓰기 되지 않을 때까지 대기(사이즈 검사를 반복하여 이전의 결과와 같은 크기이면 쓰기가 완료되었다고 판단)
		// 지속적으로 사이즈를 조회하는 도중 조회 결과가 CURLcode::CURLE_OK가 아니면 0을 반환함.
		static size_t wait_until_file_is_not_writing(CURL* curl, const std::filesystem::path& remote_path);
		
		// 파일 다운로드(파일이 담긴 바이너리 스트링을 반환)
		// 다운로드 결과가 CURLcode::CURLE_OK가 아니면 빈 문자열을 반환함.
		static std::basic_string<uint8_t> download_file(CURL* curl, const std::filesystem::path& remote_path, size_t reserve_size_hint = 0ULL);
	};
};