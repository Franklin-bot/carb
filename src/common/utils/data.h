#pragma once

#include <cstdint>
#include <map>
#include <fmt/format.h>
#include <string>

struct Ticker_Info{
    uint64_t price;
    uint64_t timestamp;
    uint64_t best_ask;
    uint64_t best_bid;
    uint64_t best_ask_q;
    uint64_t best_bid_q;


    Ticker_Info(uint64_t price, uint64_t timestamp, uint64_t best_ask, uint64_t best_bid, uint64_t best_ask_q, uint64_t best_bid_q)
      : price(price), 
        timestamp(timestamp),
        best_ask(best_ask),
        best_bid(best_bid),
        best_ask_q(best_ask_q),
        best_bid_q(best_bid_q)
    {};

    std::string toString(std::string_view ticker) const {
        return fmt::format("{},{},{},{},{},{},{}\n",
            ticker, timestamp, price, best_ask, best_bid, best_ask_q, best_bid_q);
    }


};

struct Orderbook_Info{
    uint64_t timestamp;
    std::map<uint64_t, uint64_t> bids;
    std::map<uint64_t, uint64_t> asks;

    Orderbook_Info(uint64_t timestamp) : timestamp(timestamp) {};

    std::string toString(std::string_view ticker) const {
        std::string res;
        for (const auto& [price, quantity] : bids) {
            res += fmt::format("{},bid,{},{},{}\n", ticker, timestamp, price, quantity);
        }
        for (const auto& [price, quantity] : asks) {
            res += fmt::format("{},ask,{},{},{}\n", ticker,timestamp, price, quantity);
        }
        return res;
    }
};
