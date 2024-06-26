#pragma once
// std
#include <string>

// websocketpp
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

// opencv
#include <opencv2/core.hpp>

// onetbb
#include <oneapi/tbb/task_group.h>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class Websocket_client
{
public:
	Websocket_client(const std::string& uri);
	~Websocket_client();
	void get_polygon();

private:
	client c;
	void on_open(websocketpp::connection_hdl hdl);
	void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);

private:
	const std::string uri;
	client::connection_ptr con;
	oneapi::tbb::task_group tg;

public:
	std::vector<cv::Point> _poly_vec;
};
