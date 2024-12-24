#pragma once

#include <string>
#include <vector>
#include <thread>
#include <filesystem>
#include "../common/sockets/coinbase_socket/coinbase_socket.hpp"
#include "../common/sockets/kraken_socket/kraken_socket.hpp"
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
    std::unordered_map<std::string, std::vector<Orderbook_Update>> Coinbase_Orderbooks;
    std::unordered_map<std::string, std::vector<Ticker_Info>> Kraken_Tickers;
    std::unordered_map<std::string, std::vector<Orderbook_Update>> Kraken_Orderbooks;
};
