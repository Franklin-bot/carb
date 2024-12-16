#include "socket.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
                                        //
Socket::Socket(const std::string& h, const int p)
    : host(h), port(std::to_string(p)){

        this->buffer = std::make_unique<beast::flat_buffer>();
        this->ioc = std::make_unique<net::io_context>();
        this->ctx = std::make_unique<ssl::context>(ssl::context::tlsv12_client);
        tcp::resolver resolver{*this->ioc};
        this->ws = std::make_unique<websocket::stream<ssl::stream<tcp::socket>>>(*this->ioc, *this->ctx);
        auto const results = resolver.resolve(this->host, this->port);
        auto ep = net::connect(beast::get_lowest_layer(*this->ws), results);

        if(!SSL_set_tlsext_host_name(this->ws->next_layer().native_handle(), this->host.c_str()))
            throw beast::system_error(
                beast::error_code(
                    static_cast<int>(::ERR_get_error()),
                    net::error::get_ssl_category()),
                "Failed to set SNI Hostname");

        this->host += ':' + this->port; 
        this->ws->next_layer().handshake(ssl::stream_base::client);

        this->ws->set_option(websocket::stream_base::decorator(
            [](websocket::request_type& req)
            {
                req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            }));

        this->ws->handshake(this->host, "/");
        std::cout << "handshake complete!\n";

}

void Socket::run(std::vector<int>& history, const int& index){

    std::cout << "Listening!\n";
    std::string text = "ping";

    while (true){
        //this->ws->write(net::buffer(text));
        //this->ws->read(this->buffer);
        //this->buffer->consume(this->buffer->size());
    }
}
