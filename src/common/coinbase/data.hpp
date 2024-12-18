#pragma once

#include <cstdint>

struct Coinbase_Ticker{
    uint32_t price;
    uint64_t timestamp;

    Coinbase_Ticker(uint32_t price, uint64_t timestamp) : price(price), timestamp(timestamp){};
};

