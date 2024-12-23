#pragma once

#include <string>
#include <vector>
#include <thread>
#include "../common/coinbase_socket.hpp"
#include "../common/kraken_socket.hpp"
#include "../common/utils/data.h"

class Scout {
public:

    Scout(const int duration, const std::vector<std::string>& targets);
    void listenAndNotJudge(int duration);
    void toCSV(std::string path);

private:
    int duration;
    std::vector<std::string> targets;
    Coinbase_Socket Coinbase;
    Kraken_Socket Kraken;
    

    std::unordered_map<std::string, std::vector<Ticker_Info>> Coinbase_Tickers;
    std::unordered_map<std::string, std::vector<Orderbook_Info>> Coinbase_Orderbooks;
    std::unordered_map<std::string, std::vector<Ticker_Info>> Kraken_Tickers;
    std::unordered_map<std::string, std::vector<Orderbook_Info>> Kraken_Orderbooks;
};
