#include "coinbase_socket.hpp"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
                                        //
Coinbase_Socket::Coinbase_Socket(std::vector<std::string>& products, std::vector<std::string>& channels) : 
    Socket("ws-feed.exchange.coinbase.com", 443, "/"),
    products(products),
    channels(channels)
{
        
    this->ws->write(net::buffer("HELLO!"));

    this->ws->read(*this->buffer);

    this->ws->close(websocket::close_code::normal);

    std::cout << beast::make_printable(this->buffer->data()) << std::endl;



}
