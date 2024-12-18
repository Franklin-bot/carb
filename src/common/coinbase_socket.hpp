#pragma once

#include "socket.hpp"

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h> // Optional for pretty output
#include <jwt-cpp/jwt.h>
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

constexpr static uint32_t precision = 10e8;

class Coinbase_Socket : public Socket {
public:

    Coinbase_Socket(const std::vector<std::string>& products, const std::vector<std::string>& channels);
    void listen(int seconds, std::unordered_map<std::string, std::vector<Coinbase_Ticker>>& tickers, 
            std::unordered_map<std::string, std::map<uint32_t, uint32_t>>& orderbooks);

private:
    std::vector<std::string> products;
    std::vector<std::string> channels;
    std::string create_jwt();
    void subscribe(bool sub, const std::vector<std::string>& products, const std::vector<std::string>& channels);
    void handleTicker(const rapidjson::Document& document, std::vector<Coinbase_Ticker>& ticker);
    void handleL2(const rapidjson::Document& document, std::map<uint32_t, uint32_t>& orderbook);
};
