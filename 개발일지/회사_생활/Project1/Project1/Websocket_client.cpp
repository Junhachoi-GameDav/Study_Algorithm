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
* @brief	- 초기화 생성자
* @param	- uri 서버주소
*/
Websocket_client::Websocket_client(const std::string& uri) : uri(uri)
{
	c.init_asio();
	c.clear_access_channels(websocketpp::log::alevel::all); //로그 다 지움
	c.set_open_handler(bind(&Websocket_client::on_open, this, _1));
	c.set_message_handler(bind(&Websocket_client::on_message, this, _1, _2));//Received message 로그에 띄움
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
* @brief	- 사진불러와서 바이너리로 서버에 보내기
* @param	- hdl 웹소켓
*/
void Websocket_client::on_open(websocketpp::connection_hdl hdl)
{
	const std::filesystem::path cur_path = std::filesystem::current_path(); //현재 디렉토리 가져옴
	const std::filesystem::path img_path = cur_path / "image" / "IMG_03_0000000003_L.jpg";

	std::ifstream file(img_path, std::ios::binary);
	if (!file.is_open())
		return;

	const std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	c.send(hdl, buffer, websocketpp::frame::opcode::binary);
}

/** on_message
* @brief	- 폴리곤 벡터에 저장
* @param	- hdl 웹소켓, msg 폴리곤 메세지
*/
void Websocket_client::on_message(websocketpp::connection_hdl hdl, client::message_ptr msg)
{
	if (msg->get_opcode() != websocketpp::frame::opcode::text)
		return;

	std::cout << "Received message: " << '\n' << msg->get_payload() << '\n';
	const std::string _polygon = msg->get_payload();

	//정규포현식으로 polygon 점 분리
	const std::regex reg(R"(\d+\s\d+)");
	std::smatch matches;
	auto searchStart(_polygon.cbegin());

	while (std::regex_search(searchStart, _polygon.cend(), matches, reg))
	{
		std::istringstream iss(matches[0].str()); //matches 분리시겨줌
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
* @brief	- 서버에 접속후 폴리곤 받기
* @brief	- 다른 쓰레드에서 실행됨
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

