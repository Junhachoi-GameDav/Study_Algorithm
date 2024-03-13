#include "WebsocketClient.h"

WebsocketClient::WebsocketClient()
{
    c.init_asio();
    c.set_open_handler(bind(&WebsocketClient::on_open, this, websocketpp::lib::placeholders::_1));
    c.set_message_handler(bind(&WebsocketClient::on_message, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
}

void WebsocketClient::on_open()
{

}

void WebsocketClient::on_message(websocketpp::connection_hdl hdl, client::message_ptr msg)
{
    std::cout << "hdl: " << hdl.lock().get() << '\n' << "message: " << msg->get_payload() << '\n';
}

void WebsocketClient::send_image(const std::string& uri, const std::string& image_path)
{
    websocketpp::lib::error_code e_c;

    client::connection_ptr con = c.get_connection(uri, e_c);

    if (e_c) {
        std::cout << "could not create connection because: " << e_c.message() << std::endl;
        return;
    }

    c.connect(con);
    c.run();
}

void WebsocketClient::run()
{

}
