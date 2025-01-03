#pragma once

#include "../socket.hpp"

#include "../../utils/date.h"
#include "../../utils/time.h"
#include "../../utils/auth.h"
#include "../../utils/data.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h> // Optional for pretty output
                                    
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <boost/json.hpp>
#include <jwt-cpp/traits/boost-json/defaults.h>
#include <rapidjson/document.h>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <rapidjson/rapidjson.h>

#include <string>
#include <iostream>
#include <cstdint>
#include <cstdlib>

class Kraken_Socket : public Socket {
public:

    Kraken_Socket(const std::vector<std::string>& products, const std::vector<std::string>& channels);
    void listen(int seconds, std::unordered_map<std::string, std::vector<Ticker_Info>>& tickers, 
            std::unordered_map<std::string, std::vector<Orderbook_Update>>& orderbooks);
    
private:

    static constexpr uint32_t precision = 1e8;
    std::string token;

    std::string create_token();
    void subscribe(bool sub, const std::vector<std::string>& products, const std::vector<std::string>& channels);
    void handleTicker(const rapidjson::Document& document, std::unordered_map<std::string, std::vector<Ticker_Info>>& tickers) const;
    void handleL2(const rapidjson::Document& document, std::unordered_map<std::string, std::vector<Orderbook_Update>>& orderbooks) const;


};
