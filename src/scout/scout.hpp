#pragma once

#include <string>
#include <vector>
#include "../common/coinbase_socket.hpp"
#include "../common/coinbase/data.hpp"

class Scout {
public:

    Scout(const std::vector<std::string>& targets);

private:
    std::vector<std::string> targets;
    Coinbase_Socket Coinbase;

    std::unordered_map<std::string, std::vector<Coinbase_Ticker>> Coinbase_Tickers;
    std::unordered_map<std::string, std::map<uint32_t, uint32_t>> Coinbase_Orderbooks;
};
