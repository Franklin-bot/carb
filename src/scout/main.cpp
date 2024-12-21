#include "../common/coinbase_socket.hpp"
#include "../common/kraken_socket.hpp"
#include "scout.hpp"
#include <string>



int main(){

    const std::vector<std::string> products = {"ETH-EUR", "ETH-USD"};
    const std::vector<std::string> channels = {"ticker", "level2", "heartbeat"};
    std::unique_ptr<Coinbase_Socket> test = std::make_unique<Coinbase_Socket>(products, channels);

    return 0;


}

