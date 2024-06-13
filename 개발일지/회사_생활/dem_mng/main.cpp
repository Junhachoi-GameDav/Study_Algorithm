// std
#include <filesystem>
#include <iostream>
#include <array>
#include <string>
#include <locale>
#include <system_error>
#include <thread>

//여기에 넣어야 winsock2오류가 안난다.
#include <boost/asio.hpp>
#include <boost/system/system_error.hpp>
//
#include "dem.h"
#include "dem_manager.h"

//lib
#include <pqxx/pqxx>
//#include <pqxx/params>

using boost::asio::ip::tcp;

void handle_client(boost::asio::ip::tcp::socket&& socket, dem_manager& dem_mng)
{
	try
	{
		double temp_x;
		double temp_y;

		boost::asio::read(socket, boost::asio::buffer(&temp_x, sizeof(temp_x)));
		boost::asio::read(socket, boost::asio::buffer(&temp_y, sizeof(temp_y)));

		double temp_z = dem_mng.find_ground_height(temp_x, temp_y);
		std::cout << "temp_z value : " << temp_z << '\n';

		boost::asio::write(socket, boost::asio::buffer(&temp_z, sizeof(temp_z)));
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
	}
}

int main()
{
	dem_manager& dem_mng = dem_manager::instance();
	
	boost::asio::io_context io_context;
	tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 9090));
	
	//EPSG:5186 값을 넣을 것
		//예) x:260660.83560224736, y:431142.4319238026
	while (true)
	{
		tcp::socket socket(io_context);
		acceptor.accept(socket);

		std::thread([s = std::move(socket), &dem_mng]() mutable {
			handle_client(std::move(s), dem_mng);
			}).detach();
	}
	
	return 0;
}