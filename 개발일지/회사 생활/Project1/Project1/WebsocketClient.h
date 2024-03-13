#pragma once
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

using _client = websocketpp::client<websocketpp::config::asio_client>;

class WebsocketClient
{
public:
	WebsocketClient() 
	{
		_client.init_asio();
		_client.set_message_handler(bind(&websocket_client::on_message, this, ::_1, ::_2));
	}

public:

	void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);
	void send_image(const std::string& uri, const std::string& image_path);
};

