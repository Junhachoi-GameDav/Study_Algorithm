#include "websocket_client.h"

#include <utility>
#include <regex>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include <filesystem>

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

//�ʱ�ȭ
websocket_client::websocket_client(const std::string& uri) : uri(uri) {
    c.init_asio();
    c.clear_access_channels(websocketpp::log::alevel::all); //�α� �� ����
    c.set_open_handler(bind(&websocket_client::on_open, this, _1));
    c.set_message_handler(bind(&websocket_client::on_message, this, _1, _2));//Received message �α׿� ���
}

websocket_client::~websocket_client()
{
    if (con && con->get_state() == websocketpp::session::state::closed)
        return;

    websocketpp::lib::error_code ec;
    con->close(websocketpp::close::status::normal, "", ec);

    while (con->get_state() == websocketpp::session::state::closed)
        std::this_thread::yield();
}

void websocket_client::on_open(websocketpp::connection_hdl hdl) {
    
    //�������� ��������
    const std::filesystem::path cur_path = std::filesystem::current_path(); //���� ���丮 ������
    const std::filesystem::path img_path = cur_path / "image" / "IMG_03_0000000003_L.jpg";
    
    std::ifstream file(img_path, std::ios::binary);
    if (!file.is_open())
        return;

    const std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    c.send(hdl, buffer, websocketpp::frame::opcode::binary);
}

void websocket_client::on_message(websocketpp::connection_hdl hdl, client::message_ptr msg) {
    if (msg->get_opcode() != websocketpp::frame::opcode::text)
        return;

    std::cout << "Received message: " << msg->get_payload() << '\n';
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
        _poly_vec.push_back({ x, y }); //vector�� ����

        searchStart = matches.suffix().first;
    }

    c.stop();//Ŭ���̾�Ʈ���� ���̻� �̺�Ʈ ����
}

void websocket_client::runAndGetPolygon() {
   
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

