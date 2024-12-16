#include "scout.hpp"
#include "../common/coinbase_socket.hpp"
#include <memory>
#include <iostream>
#include <string>



int main(){

    std::string pair1 = "BTC-USD";
    std::vector<std::string> products = {pair1};
    std::vector<std::string> channels = {};
    Coinbase_Socket* test = new Coinbase_Socket(products, channels);

    return 0;


}

