#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <vector>



class Socket{
public:

    explicit Socket(const std::string& host, const int port);
    void listen(std::vector<int>& history, const int& index);

private:








};
