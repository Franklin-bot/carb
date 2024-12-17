#include "../common/coinbase_socket.hpp"
#include <string>



int main(){

    std::vector<std::string> products = {"BTC-USD", "ETH-USD"};
    std::vector<std::string> channels = {"ticker", "heartbeat"};
    Coinbase_Socket* test = new Coinbase_Socket(products, channels);

    return 0;


}

