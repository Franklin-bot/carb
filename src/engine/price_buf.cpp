#include "price_buf.hpp"

PriceBuffer::PriceBuffer(uint64_t ts, uint64_t windowed_time) 
    : windowed_time(windowed_time), ts(ts),
    length(windowed_time % ts + 1) {
    prices.reserve(length);
    times.reserve(length);
}



std::pair<uint64_t, uint64_t> PriceBuffer::histNormalDist() {
    uint64_t sum = 0;
    uint64_t sum_squared_diff = 0;


    for (auto x = prices.begin(); x != prices.end() - 1; ++x) {
        sum += *x;
    }
    for (auto x = prices.begin(); x != prices.end() - 1; ++x) {
        sum_squared_diff += std::pow(*x - mean, 2);
    }
    mean = sum / (prices.size() - 1);
    std = std::sqrt(sum_squared_diff / (prices.size() - 2));

    return std::make_pair(mean, std);
}

// Adds a price and its associated time to the buffers
void PriceBuffer::addPrice(std::pair<uint64_t, uint64_t> p) {
    if (times[0] <= p.second - windowed_time) {
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

    // TODO, just run the sampler for the past value
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
int8_t PriceBuffer::isLastPeakOrValley() {
    std::pair<uint64_t, uint64_t> interval = confWindow(1);
    std::pair<uint64_t, uint64_t> lastPricePair = lastPrice();
    uint64_t sample = lastPricePair.first;

    if (sample < interval.first) {
        return -1;  // Valley
    } else if (sample > interval.second) {
        return 1;   // Peak
    } else {
        return 0;   // None
    }
}

uint64_t PriceBuffer::interpolate(uint64_t t, uint64_t t0, uint64_t t1, uint64_t p0, uint64_t p1) {
            uint64_t alpha = (t - t0) / (t1 - t0);
            return p0 + alpha * (p1 - p0);

}

void PriceBuffer::samplePrices() {
    sampled_prices.clear();

    uint64_t start_time = times.front();
    uint64_t end_time = times.back();

    for (uint64_t t = start_time; t <= end_time; t += ts) {
        auto it = std::lower_bound(times.begin(), times.end(), t);
        
        if (it == times.begin()) {
            sampled_prices.push_back(
                std::pair<uint64_t, uint64_t>(prices.front(), start_time));
        } else if (it == times.end()) {
            sampled_prices.push_back(
                std::pair<uint64_t, uint64_t>(prices.back(), end_time));
        } else {
            size_t index = std::distance(times.begin(), it);


            // linear interp
            uint64_t t0 = times[index - 1];
            uint64_t t1 = times[index];
            uint64_t p0 = prices[index - 1];
            uint64_t p1 = prices[index];
            
            uint64_t interpolated_price = interpolate(t, t0, t1, p0, p1);

            /* other interpolations
                // stepwise interp
                uint64_t interpolated_price = p0;
            */

            sampled_prices.push_back(std::pair<uint64_t, uint64_t>(interpolated_price, t));

        }
    }
}