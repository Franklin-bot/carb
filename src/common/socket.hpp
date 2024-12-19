#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <string_view>
#include <memory>
#include <vector>
#include <unistd.h>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/beast/websocket/stream_base.hpp>
#include <iostream>

class Socket{
public:

    Socket(const std::string_view host, const int port, const std::string_view path);
    ~Socket();
    void write(const std::string& msg);
    void connect();
    void close();
    void listen();


protected:

    std::string host;
    std::string path;
    std::string port;

    boost::beast::flat_buffer buffer;
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ssl::context ctx;
    boost::beast::websocket::stream<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> ws;









};
