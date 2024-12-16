#include "socket.hpp"

#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h> // Optional for pretty output


class Coinbase_Socket : public Socket {
public:

    Coinbase_Socket(std::vector<std::string>& products, std::vector<std::string>& channels);
    void subscribe(std::string& msg);
    

private:
    std::vector<std::string> products;
    std::vector<std::string> channels;
    std::string subscripStr(std::string& pair);
};
