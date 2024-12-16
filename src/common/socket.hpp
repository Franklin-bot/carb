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



class Socket{
public:

    Socket(const std::string_view host, const int port);
    void listen(std::vector<int>& history, const int& index);

private:

    std::string host;
    int port;
    std::unique_ptr<boost::beast::websocket::stream<boost::asio::ip::tcp::socket>> ws;
    std::unique_ptr<boost::beast::flat_buffer> buffer;
    std::unique_ptr<boost::asio::io_context> ioc;









};
