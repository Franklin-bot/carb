#include "scout.hpp"
#include "../common/coinbase_socket.hpp"
#include <memory>
#include <iostream>
#include <string>



int main(){

    std::vector<std::string> products = {};
    std::vector<std::string> channels = {};
    Coinbase_Socket* test = new Coinbase_Socket(products, channels);

    return 0;


}

