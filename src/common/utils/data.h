#pragma once

#include <cstdint>
#include <map>
#include <fmt/format.h>
#include <string>

struct Ticker_Info{
    std::string ticker;
    uint64_t timestamp;
    uint64_t price;
    uint64_t best_ask;
    uint64_t best_bid;
    uint64_t best_ask_q;
    uint64_t best_bid_q;

    Ticker_Info(std::string ticker, uint64_t timestamp, uint64_t price, uint64_t best_ask, uint64_t best_bid, uint64_t best_ask_q, uint64_t best_bid_q)
      : ticker(ticker),
        timestamp(timestamp),
        price(price), 
        best_ask(best_ask),
        best_bid(best_bid),
        best_ask_q(best_ask_q),
        best_bid_q(best_bid_q)
    {};

    std::string toString() const {
        return fmt::format("{},{},{},{},{},{},{}\n",
            ticker, timestamp, price, best_ask, best_bid, best_ask_q, best_bid_q);
    }


};


struct Orderbook_Update{
    std::string ticker;
    uint64_t timestamp;
    std::string side;
    uint64_t new_price;
    uint64_t new_quantity;

    Orderbook_Update() : timestamp(0){};
    Orderbook_Update(std::string ticker, uint64_t timestamp, std::string side, uint64_t price, uint64_t quantity)
        : ticker(ticker),
        timestamp(timestamp),
        side(side),
        new_price(price),
        new_quantity(quantity)
    {};

    std::string toString() const {
        return fmt::format("{},{},{},{},{}\n", 
                ticker, timestamp, side, new_price, new_quantity);
    }
};

inline std::vector<std::string> format_pair(const std::vector<std::string>& tickers, const char delimiter){

    std::vector<std::string> res;
    std::transform(tickers.begin(), tickers.end(), std::back_inserter(res), [delimiter](const std::string& ticker){
        return ticker + delimiter + "USD";
    });
    return res;

}
