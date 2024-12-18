#pragma once

#include <vector>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <utility>

class PriceBuffer
{

private: 
    std::vector<int64_t> prices;
    std::vector<uint64_t> times;

    // price, time
    std::vector<std::pair<uint64_t, uint64_t>> sampled_prices;
    uint64_t ts;
    uint16_t length;

    uint64_t mean;
    uint64_t std;

    uint64_t windowed_time;

    // returns a window of values that are statistically segnificant
    std::pair<uint64_t, uint64_t> confWindow(double z_score);

    // -1 if valley, 0 is none, 1 if peak
    std::pair<uint64_t, uint64_t> histNormalDist();
    uint64_t interpolate(uint64_t t, uint64_t t0, uint64_t t1, uint64_t p0, uint64_t p1)
    

public:
    PriceBuffer(uint64_t windowed_time, uint64_t ts);

    void samplePrices();
    void addPrice(std::pair<uint64_t, uint64_t> p);
    std::pair<uint64_t, uint64_t> lastPrice();

    int8_t isLastPeakOrValley();
};