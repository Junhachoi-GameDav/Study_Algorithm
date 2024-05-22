//#include <boost/asio.hpp>
//#include <iostream>
////#include <tbb/task_group.h>
//
//int main() {
//    using boost::asio::ip::tcp;
//    try {
//        boost::asio::io_context io_context;
//
//        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));
//
//        while (true) {
//            tcp::socket socket(io_context);
//            acceptor.accept(socket);
//
//            tcp::endpoint client_endpoint = socket.remote_endpoint();
//            std::string client_address = client_endpoint.address().to_string();
//            
//            std::string data;
//            boost::asio::streambuf buffer;
//            boost::asio::read_until(socket, buffer, "\n");
//            std::istream is(&buffer);
//            std::getline(is, data);
//
//            std::cout << "Message from" << client_address << " : " << data << std::endl;
//        }
//        //tg.wait();
//    }
//    catch (std::exception& e) {
//        std::cerr << "Exception: " << e.what() << "\n";
//    }
//
//    return 0;
//}
