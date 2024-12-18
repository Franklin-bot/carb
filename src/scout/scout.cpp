#include "scout.hpp"

Scout::Scout(const std::vector<std::string>& targets) : targets(targets){

    std::cout << "initializing scout\n";
    std::vector<std::string> Coinbase_Channels{"ticker", "level2", "heartbeat"};
    std::cout << "initializing coinbase socket\n";
    this->Coinbase = new Coinbase_Socket(this->targets, Coinbase_Channels);
    std::cout << "initialization complete\n";
    this->Coinbase->listen(10, this->Coinbase_Tickers, this->Coinbase_Orderbooks);
}
