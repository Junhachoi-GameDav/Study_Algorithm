#include <boost/asio.hpp>
#include <iostream>
#include <csignal>

void program_end(int signal)
{
    exit(signal);
}

int main() {
    using boost::asio::ip::tcp;
    signal(SIGINT, program_end);

    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        //auto endpoints = resolver.resolve("127.0.0.1", "8080");
        auto endpoints = resolver.resolve("175.116.181.37", "8080");

        tcp::socket socket(io_context);
        while (true)
        {
            std::cout << "Enter message: ";
            std::string message;
            std::getline(std::cin, message);
            message += "\n";
            if (!socket.is_open())
                socket.connect(*endpoints.begin());
            
            boost::asio::write(socket, boost::asio::buffer("Host : " + message));
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
