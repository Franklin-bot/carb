#pragma once

#include "socket.hpp"

#include <iostream>
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
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <boost/json.hpp>
#include "../common/utils/base64.h"

class Coinbase_Socket : public Socket {
public:

    Coinbase_Socket(std::vector<std::string>& products, std::vector<std::string>& channels);
    void subscribe(bool sub, std::vector<std::string>& products, std::vector<std::string>& channels);
    

private:
    std::vector<std::string> products;
    std::vector<std::string> channels;
    std::string CalcHmacSHA256(std::string_view decodedKey, std::string_view msg);
};
