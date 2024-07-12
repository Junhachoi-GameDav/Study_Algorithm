#pragma once
// std
#include <semaphore>
// cpprestsdk
#include <cpprest/http_listener.h>

// boost
#include <boost/asio.hpp>

// oneTBB
#include <oneapi/tbb/task_group.h>
/**
 * @brief 촬영 시작/종료 신호를 받는 클래스, 하나라고 가정하고 싱글턴으로 구현
 * 신호는 GCS에서 받는 것으로 협의되어 있으며 HTTP POST request로 한다.
 * 촬영에 관여하는 드론이 n대이면 리퀘스트도 n개가 온다고 가정한다.
 * 사양 변경 시 구현도 변경할 것
 * 촬영 신호를 받으면 드론에 전파한다.
*/
class signal_receiver
{
	web::http::experimental::listener::http_listener listener;
	std::binary_semaphore bsmph;

	signal_receiver();
	~signal_receiver();
	
public:
	static signal_receiver& instance()
	{
		static signal_receiver instance;
		return instance;
	}
	//int estimated_drone_count = 0;

	// 촬영 시작됨/종료됨을 담아두는 std::map
	// key : address(IP)
	// value : 촬영 signal, 시작됨(true) / 종료됨(false) 신호
	// HTTP POST request가 오면 이 맵에 (해당 주소, true) pair를 삽입한다.
	// 그리고 FTP로 해당 주소에 접속하여 파일을 다운로드하며 false가 되기를 기다린다.
	// false가 되었다 하여 파일 다운로드를 즉시 종료하지는 않는다.
	// 해당 촬영분을 모두 다운로드 한 뒤 파일 다운로드를 종료하며 std::map에서 해당 pair를 삭제한다.
	std::map<std::string, bool> acquisition_status;

	// heading 값을 담아두는 std::map
	// key : address(IP)
	// value : heading 값(double)
	// HTTP POST request가 오면 이 맵에 (해당 주소, heading) pair를 삽입한다.
	// 
	std::map<std::string, double> initial_headings;

	void remove_drone(const std::string& drone_address);
	void remove_heading(const std::string& drone_address);
};
