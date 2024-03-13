#include "WebsocketClient.h"
#include <iostream>


websocket_client::websocket_client() {
    _client.init_asio();
    _client.set_message_handler(bind(&websocket_client::on_message, this, ::_1, ::_2));
}

void WebsocketClient::on_message(websocketpp::connection_hdl hdl, client::message_ptr msg)
{
    std::cout << "hdl: " << hdl.lock().get() << '\n' << "message: " << msg->get_payload() << '\n';
}

void WebsocketClient::send_image(const std::string& uri, const std::string& image_path)
{
    websocketpp::lib::error_code e_c;

    client::connection_ptr con = _client.get_connection(uri, ec);

    if (ec) {
        std::cout << "could not create connection because: " << ec.message() << std::endl;
        return;
    }

    _client.connect(con);
    _client.run();
}
