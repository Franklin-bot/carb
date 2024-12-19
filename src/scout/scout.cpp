#include "scout.hpp"

Scout::Scout(const std::vector<std::string>& targets)
    : targets(targets),
      Coinbase(targets, {"ticker", "level2", "heartbeat"}){

    Coinbase.listen(10, Coinbase_Tickers, Coinbase_Orderbooks);
}
