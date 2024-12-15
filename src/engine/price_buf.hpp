#pragma once

#include <vector>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <utility>

class PriceBuffer {

private:
    std::vector<int64_t> prices;
    std::vector<uint64_t> times;

    std::vector<uint64_t> sampled_prices;
    uint64_t fs;

    uint64_t mean;
    uint64_t std;

    uint16_t window_size;

    // returns a window of values that are statistically segnificant
    std::pair<uint64_t, uint64_t> confWindow(double pVal);

    // -1 if valley, 0 is none, 1 if peak
    std::pair<uint64_t, uint64_t> histNormalDist();
public:
    PriceBuffer(uint16_t window_size);

    void addPrice(std::pair<uint64_t, uint64_t> p);
    std::pair<uint64_t, uint64_t> lastPrice();

    int8_t isLastPeakOrValley();

};