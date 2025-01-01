#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <string_view>
#include <unistd.h>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/beast/websocket/stream_base.hpp>

#include <iostream>
#include <memory>
#include <vector>

class Socket{
public:

    Socket(std::string_view host, int port, std::string_view path);
    ~Socket();
    void write(const std::string& msg);
    void connect();
    void close();

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
