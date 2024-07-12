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
 * @brief �Կ� ����/���� ��ȣ�� �޴� Ŭ����, �ϳ���� �����ϰ� �̱������� ����
 * ��ȣ�� GCS���� �޴� ������ ���ǵǾ� ������ HTTP POST request�� �Ѵ�.
 * �Կ��� �����ϴ� ����� n���̸� ������Ʈ�� n���� �´ٰ� �����Ѵ�.
 * ��� ���� �� ������ ������ ��
 * �Կ� ��ȣ�� ������ ��п� �����Ѵ�.
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

	// �Կ� ���۵�/������� ��Ƶδ� std::map
	// key : address(IP)
	// value : �Կ� signal, ���۵�(true) / �����(false) ��ȣ
	// HTTP POST request�� ���� �� �ʿ� (�ش� �ּ�, true) pair�� �����Ѵ�.
	// �׸��� FTP�� �ش� �ּҿ� �����Ͽ� ������ �ٿ�ε��ϸ� false�� �Ǳ⸦ ��ٸ���.
	// false�� �Ǿ��� �Ͽ� ���� �ٿ�ε带 ��� ���������� �ʴ´�.
	// �ش� �Կ����� ��� �ٿ�ε� �� �� ���� �ٿ�ε带 �����ϸ� std::map���� �ش� pair�� �����Ѵ�.
	std::map<std::string, bool> acquisition_status;

	// heading ���� ��Ƶδ� std::map
	// key : address(IP)
	// value : heading ��(double)
	// HTTP POST request�� ���� �� �ʿ� (�ش� �ּ�, heading) pair�� �����Ѵ�.
	// 
	std::map<std::string, double> initial_headings;

	void remove_drone(const std::string& drone_address);
	void remove_heading(const std::string& drone_address);
};
