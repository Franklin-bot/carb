#include "scout.hpp"

Scout::Scout(const int duration, const std::vector<std::string>& targets)
    : duration(duration),
      targets(targets),
      Coinbase(targets, {"ticker", "level2", "heartbeat"}){

    Coinbase.listen(duration, Coinbase_Tickers, Coinbase_Orderbooks);
}

void Scout::toCSV(std::string_view path){




}
