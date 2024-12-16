#include "socket.hpp"

namespace net = boost::asio;
namespace beast = boost::beast;
using namespace boost::beast;
using namespace boost::beast::websocket;
using tcp = net::ip::tcp; 

Socket::Socket(const std::string_view host, const int port)
    : host(host), port(port){

    // initialize socket resources
    std::cout << "Initializing Socket to " << this->host << "\n";
    this->buffer = std::make_unique<boost::beast::flat_buffer>();
    this->ioc = std::make_unique<net::io_context>();
    this->ws = std::make_unique<stream<tcp::socket>>(*this->ioc);
    net::ip::tcp::resolver resolver(*this->ioc);

    try {
        // calculate endpoint
        auto const results = resolver.resolve(this->host, std::to_string(port));
        std::cout << "Found Endpoint\n";

        // establish connection
        auto ep = net::connect(ws->next_layer(), results);
        this->host += ':' + std::to_string(ep.port());
        this->ws->handshake(this->host, "/");
        std::cout << "established handshake\n";

    // temporary exception catch, eventually exceptions will be handled by the object the socket belongs to
    } catch (std::exception& e) {
        std::cout << e.what() << "\n";
    }

}

void Socket::listen(std::vector<int>& history, const int& index){

    std::cout << "Listening!\n";
    std::string text = "ping";

    while (true){
        //this->ws->write(net::buffer(text));
        //this->ws->read(this->buffer);
        //this->buffer->consume(this->buffer->size());
    }
}
