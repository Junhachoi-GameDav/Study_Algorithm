#include <boost/asio.hpp>
//#include <tbb/task_group.h>
//#include <utility>
#include <iostream>
#include <thread>

void handle_client(boost::asio::ip::tcp::socket&& socket) {
    try {
        while (true) {
            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, "\n");
            std::istream is(&buffer);
            std::string data;

            if (!std::getline(is, data)) break;

            std::cout << "Message from " << data << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << "Error handling client: " << e.what() << "\n";
    }
}

int main() {
    using boost::asio::ip::tcp;
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));
    
        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::thread([s = std::move(socket)]() mutable {
                handle_client(std::move(s));
                }).detach();
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
