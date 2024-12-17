#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <string_view>
#include <iostream>
#include <memory>
#include <vector>
#include <unistd.h>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/beast/websocket/stream_base.hpp>

class Socket{
public:

    Socket(const std::string_view host, const int port, const std::string_view path);
    ~Socket();
    void run(std::vector<int>& history, const int& index);
    void write(std::string& msg);
    void connect();
    void test();
    void close();

    // virtual int order();
    // virtual void subscribe();
    // virtual void unsubscribe();


protected:

    std::string host;
    std::string path;
    std::string port;

    std::unique_ptr<boost::asio::ip::tcp::resolver> resolver;
    std::unique_ptr<boost::beast::websocket::stream<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>> ws;
    std::unique_ptr<boost::beast::flat_buffer> buffer;
    std::unique_ptr<boost::asio::io_context> ioc;
    std::unique_ptr<boost::asio::ssl::context> ctx;









};
