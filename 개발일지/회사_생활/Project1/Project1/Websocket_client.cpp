// std
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <thread>

#include "Websocket_client.h"

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

/** Websocket_client
* @brief	- �ʱ�ȭ ������
* @param	- uri �����ּ�
*/
Websocket_client::Websocket_client(const std::string& uri) : uri(uri)
{
	c.init_asio();
	c.clear_access_channels(websocketpp::log::alevel::all); //�α� �� ����
	c.set_open_handler(bind(&Websocket_client::on_open, this, _1));
	c.set_message_handler(bind(&Websocket_client::on_message, this, _1, _2));//Received message �α׿� ���
}

Websocket_client::~Websocket_client()
{
	if (con && con->get_state() == websocketpp::session::state::closed)
		return;

	websocketpp::lib::error_code ec;
	con->close(websocketpp::close::status::normal, "", ec);

	while (con->get_state() == websocketpp::session::state::closed)
		std::this_thread::yield();
}

/** on_open
* @brief	- �����ҷ��ͼ� ���̳ʸ��� ������ ������
* @param	- hdl ������
*/
void Websocket_client::on_open(websocketpp::connection_hdl hdl)
{
	const std::filesystem::path cur_path = std::filesystem::current_path(); //���� ���丮 ������
	const std::filesystem::path img_path = cur_path / "image" / "IMG_03_0000000003_L.jpg";

	std::ifstream file(img_path, std::ios::binary);
	if (!file.is_open())
		return;

	const std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	c.send(hdl, buffer, websocketpp::frame::opcode::binary);
}

/** on_message
* @brief	- ������ ���Ϳ� ����
* @param	- hdl ������, msg ������ �޼���
*/
void Websocket_client::on_message(websocketpp::connection_hdl hdl, client::message_ptr msg)
{
	if (msg->get_opcode() != websocketpp::frame::opcode::text)
		return;

	std::cout << "Received message: " << '\n' << msg->get_payload() << '\n';
	const std::string _polygon = msg->get_payload();

	//�������������� polygon �� �и�
	const std::regex reg(R"(\d+\s\d+)");
	std::smatch matches;
	auto searchStart(_polygon.cbegin());

	while (std::regex_search(searchStart, _polygon.cend(), matches, reg))
	{
		std::istringstream iss(matches[0].str()); //matches �и��ð���
		int x;
		int y;
		iss >> x >> y;
		_poly_vec.push_back({ x, y });

		searchStart = matches.suffix().first;
	}

	websocketpp::lib::error_code ec;
	con->close(websocketpp::close::status::normal, "", ec);
}

/** get_polygon
* @brief	- ������ ������ ������ �ޱ�
* @brief	- �ٸ� �����忡�� �����
*/
void Websocket_client::get_polygon()
{
	websocketpp::lib::error_code ec;
	con = c.get_connection(uri, ec);

	if (ec)
		return;

	c.connect(con);
	tg.run([this]()->void
		{
			c.run();
		});
	tg.wait();
}

