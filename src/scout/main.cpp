#include "../common/coinbase_socket.hpp"
#include "../common/kraken_socket.hpp"
#include "scout.hpp"
#include <string>



int main(){

    const std::vector<std::string> products = {"ETH/USD"};
    // const std::vector<std::string> channels = {"ticker", "level2", "heartbeat"};
    const std::vector<std::string> channels = {"ticker", "book"};
    std::unique_ptr<Kraken_Socket> test = std::make_unique<Kraken_Socket>(products, channels);

    return 0;


}

