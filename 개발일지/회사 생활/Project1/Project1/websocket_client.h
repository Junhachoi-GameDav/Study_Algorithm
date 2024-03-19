#pragma once
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <opencv2/core.hpp>

#include <string>

#include <oneapi/tbb/task_group.h>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class websocket_client {
public:
    websocket_client(const std::string& uri);
    ~websocket_client();
    void runAndGetPolygon();

private:
    client c;
    void on_open(websocketpp::connection_hdl hdl);
    void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);
    
private:
    const std::string uri;
    //const std::thread thr;
    client::connection_ptr con;
    oneapi::tbb::task_group tg;

public:
    std::vector<cv::Point> _poly_vec;
};
