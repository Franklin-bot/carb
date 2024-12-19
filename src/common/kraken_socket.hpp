#pragma once

#include "socket.hpp"

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h> // Optional for pretty output
#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <boost/json.hpp>
#include "../common/utils/date.h"
#include "../common/coinbase/data.hpp"
#include "../common/utils/time.h"
#include <jwt-cpp/traits/boost-json/defaults.h>
#include <rapidjson/document.h>
#include <boost/beast/core/tcp_stream.hpp>
#include "../common/utils/auth.h"
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdlib>

class Kraken_Socket : public Socket {
public:

    Kraken_Socket(const std::vector<std::string>& products, const std::vector<std::string>& channels);


private:
    std::vector<std::string> products;
    std::vector<std::string> channels;
    std::string token;

    std::string create_token();
    void subscribe(const bool sub, const std::vector<std::string>& products, const std::vector<std::string>& channels);
    void handleTicker(const rapidjson::Document& document, std::vector<Coinbase_Ticker>& ticker);
    void handleL2(const rapidjson::Document& document, std::map<uint32_t, uint32_t>& orderbook);


};
