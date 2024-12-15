#include "../src/engine/price_buf.hpp"
#include <cassert>
#include <iostream>

// Helper function to compare two pairs
void assertPairEqual(const std::pair<uint64_t, uint64_t>& a, const std::pair<uint64_t, uint64_t>& b) {
    assert(a.first == b.first && a.second == b.second && "Pairs are not equal!");
}

void testPriceBuffer() {
    // Test 1: Create a PriceBuffer with a window size of 5
    PriceBuffer pb(5);
    
    // We cannot directly call lastPrice() on an empty buffer, it will throw an exception
    try {
        pb.lastPrice();
        assert(false && "Expected exception when calling lastPrice on an empty buffer.");
    } catch (const std::out_of_range&) {
        // Correct behavior: exception should be thrown
    }

    // Test 2: Add prices and test lastPrice()
    pb.addPrice({100, 1});
    pb.addPrice({110, 2});
    pb.addPrice({120, 3});
    pb.addPrice({130, 4});
    pb.addPrice({140, 5});
    
    // Assert the last price added
    assertPairEqual(pb.lastPrice(), std::make_pair(140, 5));
    
    // Test 3: Check for peaks and valleys
    pb.addPrice({50, 6});
    assert(pb.isLastPeakOrValley() == -1); // This should be a valley since 50 is below the conf window
    
    pb.addPrice({600, 7});
    assert(pb.isLastPeakOrValley() == 1); // This should be a peak since 160 is above the conf window

    pb.addPrice({210, 8});
    pb.addPrice({200, 9});
    pb.addPrice({200, 10});
    pb.addPrice({190, 11});
    pb.addPrice({200, 12});
    pb.addPrice({210, 13});
    pb.addPrice({200, 14});
    pb.addPrice({190, 15});
    pb.addPrice({200, 16});
    assert(pb.isLastPeakOrValley() == 0); // This should be just be noise

    // Print results
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    try {
        testPriceBuffer();
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
    }
    return 0;
}
