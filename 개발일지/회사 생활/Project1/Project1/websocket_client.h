#pragma once
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <opencv2/core.hpp>

#include <string>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class websocket_client {
public:
    websocket_client(const std::string& uri);
    ~websocket_client();
    void run();

private:
    client c;
    void on_open(websocketpp::connection_hdl hdl);
    void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);

public:
    std::string uri;
    std::string _polygon;
    std::vector<cv::Point> _poly_vec;
};
