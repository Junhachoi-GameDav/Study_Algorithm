#include <boost/asio.hpp>
#include <iostream>
//#include <tbb/task_group.h>
//#ifdef __cpp_lib_format
//constexpr auto format = std::format
//#else
//constexpr auto format = fmt::format
//#endif
//#ifdef __HAS_CXX14

int main() {
    using boost::asio::ip::tcp;
    try {
        boost::asio::io_context io_context;
        std::system("docker run ...");
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));
        //std::vector<tcp::socket> accepted_sockets;
        //tbb::task_group tg;
        //tg.run([&io_context, &tg, &acceptor, &accepted_sockets]()->void
        //    {
        //        while (true)
        //        {
        //            auto& socket_ref = accepted_sockets.emplace_back(tcp::socket(io_context));
        //            acceptor.accept(socket_ref);
        //            
        //            tg.run([&socket_ref]()->void
        //                {
        //                    while (true) {
        //                        std::string data;
        //                        boost::asio::streambuf buffer;
        //                        boost::asio::read_until(socket_ref, buffer, "\n");
        //                        std::istream is(&buffer);
        //                        std::getline(is, data);
        //
        //                        std::cout << "Message from client" << static_cast<size_t>(socket_ref.native_handle()) << ": " << data << std::endl;
        //                    }
        //                });
        //        }
        //    });

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
        
            //tcp::endpoint client_endpoint = socket.remote_endpoint();
            //std::string client_address = client_endpoint.address().to_string();
            
            std::string data;
            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, "\n");
            std::istream is(&buffer);
            std::getline(is, data);

            std::cout << "Message from " << data << std::endl;
        }
        //tg.wait();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
