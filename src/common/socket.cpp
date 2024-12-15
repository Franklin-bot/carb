#include "socket.hpp"

namespace net = boost::asio;
namespace beast = boost::beast;
using namespace boost::beast;
using namespace boost::beast::websocket;

Socket::Socket(const std::string& host, const int port){
    net::io_context ioc;
    tcp_stream sock(ioc);
    net::ssl::context ctx(net::ssl::context::tlsv12);

}


void Socket::listen(std::vector<int>& history, const int& index){

    while (true){







    }
}
