#include "../common/coinbase_socket.hpp"
#include "../common/kraken_socket.hpp"
#include "scout.hpp"
#include <string>



int main(){

    const std::vector<std::string> products = {"BTC", "ETH"};
    // const std::vector<std::string> channels = {"ticker", "level2", "heartbeat"};
    const std::vector<std::string> channels = {"ticker", "book"};
    std::unique_ptr<Scout> test = std::make_unique<Scout>(10, products);
    test->listenAndNotJudge(10);

    return 0;


}

