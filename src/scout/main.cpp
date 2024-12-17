#include "../common/coinbase_socket.hpp"
#include <string>



int main(){

    std::vector<std::string> products = {"ETH-EUR", "ETH-USD"};
    std::vector<std::string> channels = {"ticker", "heartbeat", "level2"};
    Coinbase_Socket* test = new Coinbase_Socket(products, channels);

    return 0;


}

