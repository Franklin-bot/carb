#include "scout.hpp"
#include "../common/coinbase_socket.hpp"
#include <memory>
#include <iostream>
#include <string>



int main(){

    std::vector<std::string> products = {"ETH-USD"};
    std::vector<std::string> channels = {"ticker", "heartbeat"};
    Coinbase_Socket* test = new Coinbase_Socket(products, channels);

    return 0;


}

