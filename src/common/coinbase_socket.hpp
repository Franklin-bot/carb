#include "socket.hpp"

#include <iostream>
#include <cstdlib>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h> // Optional for pretty output


class Coinbase_Socket : public Socket {
public:

    Coinbase_Socket(std::vector<std::string>& products, std::vector<std::string>& channels);
    void subscribe(bool sub, std::vector<std::string>& products, std::vector<std::string>& channels);
    

private:
    std::vector<std::string> products;
    std::vector<std::string> channels;
};
