#include "socket.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
                                        //
Socket::Socket(std::string_view host, int port, std::string_view path)
      : host(host), port(std::to_string(port)), path(path), 
        buffer(),
        ioc(),
        resolver(ioc),
        ctx(ssl::context::tlsv13_client),
        ws(ioc, ctx){
        }

void Socket::write(const std::string& msg) { 
    ws.write(net::buffer(msg));
}

void Socket::connect() {
        tcp::resolver resolver{ioc};
        auto results = resolver.resolve(host, port);

        auto ep = net::connect(beast::get_lowest_layer(ws), results);

        if(!SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str()))
            throw beast::system_error(
                beast::error_code(
                    static_cast<int>(::ERR_get_error()),
                    net::error::get_ssl_category()),
                "Failed to set SNI Hostname");

        host += ':' + port; 
        ws.next_layer().handshake(ssl::stream_base::client);
        ws.set_option(websocket::stream_base::decorator(
            [](websocket::request_type& req)
            {
                req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            }));

        ws.handshake(host, path);
        std::cout << "handshake complete, connected!\n";
}

void Socket::close() {
    if(beast::get_lowest_layer(ws).is_open()) {
        try {
            ws.close(websocket::close_code::normal);
        } catch (boost::system::system_error& e){
            if (e.code() != boost::asio::ssl::error::stream_truncated) throw;
        }
    }
}

Socket::~Socket() {
    close();
    std::cout << "socket deleted!\n";
}

