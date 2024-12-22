#include "scout.hpp"
#include <fstream>

Scout::Scout(const int duration, const std::vector<std::string>& targets)
    : duration(duration),
      targets(targets),
      Coinbase(format_pair(targets, '-'), {"ticker", "level2", "heartbeat"}),
      Kraken(format_pair(targets, '/'), {"ticker", "book"}){

    // Coinbase.listen(duration, Coinbase_Tickers, Coinbase_Orderbooks);
    Kraken.listen(duration, Kraken_Tickers, Kraken_Orderbooks);
    toCSV(std::filesystem::current_path().parent_path()/"data");
}

void Scout::toCSV(std::string path){

    std::ofstream output;
    std::string coinbase_ticker_path = path + "/coinbase_tickers.txt";
    std::string coinbase_book_path = path + "/coinbase_books.txt";
    std::string kraken_ticker_path = path + "/kraken_tickers.txt";
    std::string kraken_book_path = path + "/kraken_books.txt";

    output.open(coinbase_ticker_path);
    if (!output.is_open()) {
        std::cerr << "Failed to open file: " << coinbase_ticker_path << "\n";
        return;
    }
    for (const auto& pair : Coinbase_Tickers){
        for (const Ticker_Info& t : pair.second){
            output << t.toString(pair.first);
        }
    }
    output.close();
    std::cout << "Wrote ticker data: " << coinbase_ticker_path << "\n";
    output.open(coinbase_book_path);
    if (!output.is_open()) {
        std::cerr << "Failed to open file: " << coinbase_book_path << std::endl;
        return;
    }
    for (const auto& pair: Coinbase_Orderbooks){
        for (const Orderbook_Info& t : pair.second){
            output << t.toString(pair.first);
        }
    }
    output.close();
    std::cout << "Wrote orderbook data: " << coinbase_book_path << "\n";

    output.open(kraken_ticker_path);
    if (!output.is_open()) {
        std::cerr << "Failed to open file: " << kraken_ticker_path << "\n";
        return;
    }
    for (const auto& pair : Kraken_Tickers){
        for (const Ticker_Info& t : pair.second){
            output << t.toString(pair.first);
        }
    }
    output.close();
    std::cout << "Wrote ticker data: " << kraken_ticker_path << "\n";
    output.open(kraken_book_path);
    if (!output.is_open()) {
        std::cerr << "Failed to open file: " << kraken_book_path << std::endl;
        return;
    }
    for (const auto& pair: Kraken_Orderbooks){
        for (const Orderbook_Info& t : pair.second){
            output << t.toString(pair.first);
        }
    }
    output.close();
    std::cout << "Wrote orderbook data: " << kraken_book_path << "\n";
}
