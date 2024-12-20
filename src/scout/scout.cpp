#include "scout.hpp"
#include <fstream>

Scout::Scout(const int duration, const std::vector<std::string>& targets)
    : duration(duration),
      targets(targets),
      Coinbase(targets, {"ticker", "level2", "heartbeat"}){

    Coinbase.listen(duration, Coinbase_Tickers, Coinbase_Orderbooks);
    toCSV(std::filesystem::current_path().parent_path()/"data");
}

void Scout::toCSV(std::string path){

    std::ofstream output;
    std::string ticker_path = path + "/coinbase_tickers.txt";
    std::string book_path = path + "/coinbase_books.txt";

    output.open(ticker_path);
    if (!output.is_open()) {
        std::cerr << "Failed to open file: " << ticker_path << "\n";
        return;
    }
    for (const auto& pair : Coinbase_Tickers){
        for (const Ticker_Info& t : pair.second){
            output << t.toString(pair.first);
        }
    }
    output.close();
    std::cout << "Wrote ticker data: " << ticker_path << "\n";
    output.open(book_path);
    if (!output.is_open()) {
        std::cerr << "Failed to open file: " << book_path << std::endl;
        return;
    }
    for (const auto& pair: Coinbase_Orderbooks){
        for (const Orderbook_Info& t : pair.second){
            output << t.toString(pair.first);
        }
    }
    output.close();
    std::cout << "Wrote orderbook data: " << book_path << "\n";
}
