// std
#include <filesystem>
#include <iostream>
#include <array>
#include <string>
#include <locale>
#include <system_error>

//���⿡ �־�� winsock2������ �ȳ���.
#include <boost/asio.hpp>
#include <boost/system/system_error.hpp>
//
#include "dem.h"
#include "dem_manager.h"

//lib
#include <pqxx/pqxx>
//#include <pqxx/params>

using boost::asio::ip::tcp;

int main()
{

	dem_manager& dem_mng = dem_manager::instance();
	
	boost::asio::io_context io_context;
	tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 9090));
	
	//EPSG:5186 ���� ���� ��
		//��) x:260660.83560224736, y:431142.4319238026
	while (true)
	{
		tcp::socket socket(io_context);
		acceptor.accept(socket);

		double temp_x;
		double temp_y;
		boost::asio::read(socket, boost::asio::buffer(&temp_x, sizeof(temp_x)));
		boost::asio::read(socket, boost::asio::buffer(&temp_y, sizeof(temp_y)));

		double temp_z = dem_mng.find_ground_height(temp_x, temp_y);

		std::cout << "temp_z value : " << temp_z << '\n';
		boost::asio::write(socket, boost::asio::buffer(&temp_z, sizeof(temp_z)));
	}
	
	return 0;
}