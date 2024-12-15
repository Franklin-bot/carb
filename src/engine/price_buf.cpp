#include "price_buf.hpp"

PriceBuffer::PriceBuffer(uint16_t window_size) : window_size(window_size) {
    prices.reserve(window_size+1);
    times.reserve(window_size+1);
}

std::pair<uint64_t, uint64_t> PriceBuffer::histNormalDist() {
    uint64_t sum = 0;
    uint64_t sum_squared_diff = 0;

    for (uint64_t value : prices) {
        sum += value;
    }
    for (uint64_t value : prices) {
        sum_squared_diff += std::pow(value - mean, 2);
    }
    mean = sum / prices.size();
    std = std::sqrt(sum_squared_diff / (prices.size() - 1));

    return std::make_pair(mean, std);
}

// Adds a price and its associated time to the buffers
void PriceBuffer::addPrice(std::pair<uint64_t, uint64_t> p) {
    if (prices.size() >= window_size + 1) {
        prices.erase(prices.begin());
        times.erase(times.begin());
    }
    prices.push_back(p.first);
    times.push_back(p.second);
}

// Returns the last price added to the buffer
std::pair<uint64_t, uint64_t> PriceBuffer::lastPrice() {

    if (prices.empty() || times.empty()) {
        throw std::out_of_range("No prices in the buffer");
    }

    return std::make_pair(prices.back(), times.back());
}

// Returns a window of values that are statistically significant based on Z score
std::pair<uint64_t, uint64_t> PriceBuffer::confWindow(double z_score) {
    std::pair<uint64_t, uint64_t> lastPricePair = lastPrice();

    uint64_t sample = lastPricePair.first;
    std::pair<uint64_t, uint64_t> dist = histNormalDist();

    mean = dist.first;
    std = dist.second;

    uint64_t low = mean - (z_score * std);
    uint64_t high = mean + (z_score * std);

    return std::make_pair(low, high);
}



// Determines if a sample is a peak, valley, or none within the given interval
int8_t PriceBuffer::isPeakOrValley(uint64_t sample, std::pair<uint64_t, uint64_t> interval) {
    if (sample < interval.first) {
        return -1;  // Valley
    } else if (sample > interval.second) {
        return 1;   // Peak
    } else {
        return 0;   // None
    }
}

