// std
#include <regex>
#include <print>

#include "drone.h"
//#include "../global_logger.h"

// �̻��
std::filesystem::path drone::remote::find_target_directory(CURL* curl, drone_db_connection& db_con, const std::string& address, const int port)
{
	const std::filesystem::path default_remote_directory = std::format("ftp://{}:{}/ssd", address, port);
	std::vector<std::filesystem::path> list_dir_ssd;
	
	do
	{
		// ���丮 ��ȸ �� ���͸� �Ͽ� ���� �ֱ� �ð��� ���丮���� �˻�
		list_dir_ssd = remote::list_directory(curl, default_remote_directory);
		if (list_dir_ssd.empty())
		{
			std::format("{}:{} cannot list default directory of drone.\ncould be either camera is off or network issue\nretry...\n", address, port);
			continue;
		}

		// ��� Ÿ�缺 Ȯ��
		std::erase_if(list_dir_ssd, [](const std::filesystem::path& path)->bool
		{
			if (path.empty())
				return true;

			const std::string directory_string = path.generic_string();

			// ��¥ �� �ð� ����("yy-MM-dd_hh-mm") �̸��� �ƴ� ���丮 ���͸�
			if (not std::regex_match(directory_string, std::regex("[0-9]{2}-[0-9]{2}-[0-9]{2}_[0-9]{2}-[0-9]{2}", std::regex::optimize)))
				return true;

			// 1970�� 1�� 1���ڷ� ������ ���丮 ���͸�(���� ���� �߿� ������ �����ϴ� ��� ���丮 ���� ������� �ʾ� �̷� ���丮 �˻���)
			if (directory_string.substr(0, 8) == "70-01-01")
				return true;

			return false;
		});

		// ���� �ֱ� �ð��� ���丮�� ������ ���丮 ��󿡼� ����
		std::erase_if(list_dir_ssd, [recent_dir = *list_dir_ssd.rbegin()](const std::filesystem::path& path)->bool
		{
			return path.generic_string() < recent_dir.generic_string();
		});

		// DB�� �����Ͽ� �ش� ���丮�� �ִ��� �˻�
		//std::erase_if(list_dir_ssd, [&db_con, &default_remote_directory](const std::filesystem::path& path)->bool
		//{
		//	// �̹� �ִ� ���丮�� ������ �ٿ�ε� �޾Ҵ� ����̹Ƿ� ��� �ƴ�
		//	const auto select_directory_result =
		//		db_con.select_query_directory(std::format("remote_dir = '{}'", (default_remote_directory / path / "img").generic_string()));

		//	return not select_directory_result.empty();
		//});
	} while (list_dir_ssd.empty());
	
	
	list_dir_ssd = remote::list_directory(curl, default_remote_directory);

	return default_remote_directory / (*list_dir_ssd.rbegin()) / "img";
}

std::vector<std::filesystem::path> drone::remote::list_directory(CURL* curl, const std::filesystem::path& remote_path)
{
	assert(curl != nullptr);
	assert(not remote_path.empty());

	class __dir_list_only
	{
		CURL* curl;

	public:
		// ctor : set DIRLISTONLY option to true
		__dir_list_only(CURL* c) : curl(c) { curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 1L); }
		// dtor : set DIRLISTONLY option to false after the operation has done
		~__dir_list_only() { curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 0L); }
	} dirlist_only(curl);

	// ���丮 ��ȸ �� ��� �������� /�� �پ�� �Ѵ�.
	curl_easy_setopt(curl, CURLOPT_URL, (remote_path.generic_string() + "/").c_str());

	std::string data;
	//std::println("list_directory_CURLcode = curl_easy_setopt = data");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
	//std::println("list_directory_CURLcode = curl_easy_setopt = write_callback_string");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_callback_string<std::string>);

	//std::println("list_directory_CURLcode = curl_easy_perform");
	CURLcode res = curl_easy_perform(curl);
	
	if (res != CURLcode::CURLE_OK)
	{
		std::println("list_directory_CURLcode = not OK - {} , NO. {}", curl_easy_strerror(res), static_cast<int>(res));
		return {};
	}

	std::istringstream iss(data);

	std::vector<std::filesystem::path> entries;
	std::string line;
	while (std::getline(iss, line))
	{
		std::erase(line, '\r');
		std::u8string convertedu8(line.begin(), line.end());

		if (line == "." || line == "..")
			continue;

		entries.push_back(convertedu8);
	}

	std::sort(entries.begin(), entries.end());

	return entries;
}

size_t drone::remote::wait_until_file_is_not_writing(CURL* curl, const std::filesystem::path& remote_path)
{
	assert(curl != nullptr);
	assert(not remote_path.empty());

	// ������ �ҷ����� ���� �ƴ϶� ���� ����� ������(����� ���ϱ� ����)
	class __header_only
	{
		CURL* ptr;
	public:
		__header_only(CURL* curl) : ptr(curl)
		{
			curl_easy_setopt(ptr, CURLOPT_NOBODY, 1L);
			curl_easy_setopt(ptr, CURLOPT_HEADER, 1L);
		}

		~__header_only()
		{
			curl_easy_setopt(ptr, CURLOPT_NOBODY, 0L);
			curl_easy_setopt(ptr, CURLOPT_HEADER, 0L);
		}
	} header_only(curl);

	// ���� �ּ� ����
	curl_easy_setopt(curl, CURLOPT_URL, remote_path.generic_string().c_str());

	// �����δ� �ݹ鵵 ȣ��ǰ� ��Ʈ�� ���·� ���� �����Ͱ� ������ �ؿ��� CURLINFO::CURLINFO_CONTENT_LENGTH_DOWNLOAD_T �±׷�
	// curl_easy_getinfo�� �ϸ� ����� ���� �� �ֱ� ������ ���� ��Ʈ�� �Ľ��� ���� �� �ʿ�� ����.
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_callback_noop);
	
	// ���� ������ 1ȸ ȣ���ϴ� ���� ����
	const auto get_file_size = [&curl]()->size_t
	{
		size_t size;
		CURLcode res = curl_easy_perform(curl);
		
		// ���� ������ �ޱ⿡ ������ ��� 0 ��ȯ
		if (res != CURLcode::CURLE_OK)
		{
			std::println("get_file_size_CURLcode = not OK - {} , NO. {}", curl_easy_strerror(res), static_cast<int>(res));
			return 0ULL;
		}

		curl_easy_getinfo(curl, CURLINFO::CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &size);
		return size;
	};

	size_t sz0 = get_file_size();
	if (sz0 == 0ULL)
	{
		std::println("sz0 == 0ULL");
		return 0ULL;
	}

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		const size_t sz1 = get_file_size();

		if (sz1 == 0ULL)
		{
			std::println("sz1 == 0ULL");
			return 0ULL;
		}

		if (sz1 != sz0)
		{
			sz0 = sz1;
			continue;
		}

		return sz1;
	}
}

std::basic_string<uint8_t> drone::remote::download_file(CURL* curl, const std::filesystem::path& remote_path, size_t reserve_size_hint)
{
	assert(curl != nullptr);
	assert(not remote_path.empty());

	const std::string full_url = remote_path.generic_string();

	curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());

	std::basic_string<uint8_t> content;
	if (reserve_size_hint != 0ULL)
		content.reserve(reserve_size_hint);

	std::println("download_file_CURLcode = curl_easy_setopt = content");//�� �Ȱɸ�
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
	std::println("download_file_CURLcode = curl_easy_setopt = write_callback_string");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_callback_string<std::basic_string<uint8_t>>);

	std::println("download_file_CURLcode = curl_easy_perform");
	CURLcode res = curl_easy_perform(curl); 

	if (res != CURLcode::CURLE_OK)
	{
		std::println("download_file_CURLcode = not OK - {} , NO. {}", curl_easy_strerror(res), static_cast<int>(res));
		return {};
	}

	return content;
}