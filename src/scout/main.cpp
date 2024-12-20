#include "../common/coinbase_socket.hpp"
#include "../common/kraken_socket.hpp"
#include "scout.hpp"
#include <string>



int main(){

    const std::vector<std::string> products = {"ETH-EUR", "ETH-USD"};
    const std::vector<std::string> channels = {"ticker", "level2", "heartbeat"};
    std::unique_ptr<Scout> test = std::make_unique<Scout>(10, products);

    return 0;


}

