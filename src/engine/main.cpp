#include "scout.hpp"
#include "../common/socket.hpp"
#include <memory>
#include <iostream>
#include <string>



int main(){

    std::vector<std::string> exchanges {"coinbase", "kraken"};
    std::vector<std::string> coins {"Shiba Inu"};

    auto port = 8080;
    Socket* test = new Socket(std::string("example.com"), 8080);
    delete(test);

    return 0;
}
