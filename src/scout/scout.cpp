#include "scout.hpp"
#include <fstream>

Scout::Scout(const int duration, const std::vector<std::string>& targets)
    : duration(duration),
      targets(targets),
      Coinbase(format_pair(targets, '-'), {"ticker", "level2", "heartbeat"}),
      Kraken(format_pair(targets, '/'), {"ticker", "book"}){
}

void Scout::listenAndNotJudge(int duration){

    std::thread t1([this, duration](){this->Coinbase.listen(duration, this->Coinbase_Tickers, this->Coinbase_Orderbooks);});
    std::thread t2([this, duration](){this->Kraken.listen(duration, this->Kraken_Tickers, this->Kraken_Orderbooks);});

    t1.join();
    t2.join();

    toCSV(std::filesystem::current_path().parent_path()/"data");

}

void Scout::toCSV(std::string path){

    std::ofstream output;
    std::string coinbase_ticker_path = path + "/coinbase_tickers.txt",
                coinbase_book_path = path + "/coinbase_books.txt",
                kraken_ticker_path = path + "/kraken_tickers.txt",
                kraken_book_path = path + "/kraken_books.txt";

    output.open(coinbase_ticker_path);
    if (!output.is_open()) {
        std::cerr << "Failed to open file: " << coinbase_ticker_path << "\n";
        return;
    }
    for (const auto& pair : Coinbase_Tickers){
        for (const Ticker_Info& t : pair.second){
            output << t.toString();
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
        for (const Orderbook_Update& t : pair.second){
            output << t.toString();
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
            output << t.toString();
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
        for (const Orderbook_Update& t : pair.second){
            output << t.toString();
        }
    }
    output.close();
    std::cout << "Wrote orderbook data: " << kraken_book_path << "\n";
}
