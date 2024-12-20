#pragma once

#include <string>
#include <vector>
#include "../common/coinbase_socket.hpp"
#include "../common/utils/data.h"
#include <fstream>

class Scout {
public:

    Scout(const int duration, const std::vector<std::string>& targets);
    void toCSV(std::string path);

private:
    int duration;
    std::vector<std::string> targets;
    Coinbase_Socket Coinbase;

    std::unordered_map<std::string, std::vector<Ticker_Info>> Coinbase_Tickers;
    std::unordered_map<std::string, std::vector<Orderbook_Info>> Coinbase_Orderbooks;
};
