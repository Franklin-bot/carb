#pragma once

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <string>

class Listener{
public:

    Listener() = delete;
    explicit Listener(const std::string_view target, int port);

private:




};
