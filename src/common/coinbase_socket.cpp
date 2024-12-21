#include "coinbase_socket.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

Coinbase_Socket::Coinbase_Socket(const std::vector<std::string>& products, const std::vector<std::string>& channels) : 
    Socket("wss://advanced-trade-ws.coinbase.com", 443, "/"),
    products(products),
    channels(channels)
{
    websocket::stream_base::timeout opt{
        std::chrono::seconds(3),
        std::chrono::seconds(2),
        false
        };
    ws.set_option(opt);
    std::cout << "connecting\n";
    connect();
    std::cout << "subscribing\n";
    subscribe(true, products, channels);
}


void Coinbase_Socket::subscribe(const bool sub, const std::vector<std::string>& p, const std::vector<std::string>& c) {

    for (const std::string& channel_id : c){

        rapidjson::Document document;
        document.SetObject();

        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        rapidjson::Value typeValue(sub ? "subscribe" : "unsubscribe", allocator);
        document.AddMember("type", typeValue, allocator);


        rapidjson::Value product_ids(rapidjson::kArrayType);
        for (const std::string& product : p){
            product_ids.PushBack(rapidjson::Value(product.c_str(), allocator), allocator);
        }
        document.AddMember("product_ids", product_ids, allocator);
        document.AddMember("channel", rapidjson::Value(channel_id.c_str(), allocator), allocator);

        if (channel_id == "level2"){
            std::string token = create_jwt();
            rapidjson::Value tokenValue(token.c_str(), allocator);
            document.AddMember("jwt", tokenValue, allocator);
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        std::cout << buffer.GetString() << std::endl;
        std::string msg = buffer.GetString();
        write(msg);
    }
}


std::string Coinbase_Socket::create_jwt(){

    std::string key_name{std::getenv("COINBASE_API_TOKEN")};
    std::string key_secret{std::getenv("COINBASE_PRIVATE_TOKEN")};

    unsigned char nonce_raw[16];
    RAND_bytes(nonce_raw, sizeof(nonce_raw));
    std::string nonce(reinterpret_cast<char*>(nonce_raw), sizeof(nonce_raw));

    auto token = jwt::create()
        .set_subject(key_name)
        .set_issuer("cdp")
        .set_not_before(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{120})
        .set_header_claim("kid", jwt::claim(key_name))
        .set_header_claim("nonce", jwt::claim(nonce))
        .sign(jwt::algorithm::es256(key_name, key_secret));

    return token;
}


void Coinbase_Socket::listen(int seconds, std::unordered_map<std::string, std::vector<Ticker_Info>>& tickers, 
        std::unordered_map<std::string, std::vector<Orderbook_Info>>& orderbooks){

    std::cout << "Begin Listening\n";
    int l2_count = 0;
    int ticker_count = 0;
    time_t end = time(0) + seconds;

    while (time(0) < end) {
        ws.read(buffer);
        std::string message = beast::buffers_to_string(buffer.data());
        rapidjson::Document document;
        document.Parse(message.c_str());

        // heavily optimize this later, remove branching
        if (document.HasMember("channel")){
            std::string channel = document["channel"].GetString();
             if (channel == "ticker"){
                 handleTicker(document, tickers);
                 ticker_count++;
             } else if (channel == "l2_data"){
                 handleL2(document, orderbooks);
                 l2_count++;
             }
        }
        buffer.clear();
        // TODO: handle errors messages here
    }
    std::cout << l2_count << " l2 messages handled\n";
    std::cout << ticker_count << " ticker messages handled\n";

    int tickers_size = 0;
    for (const auto& pair : tickers){
        tickers_size += pair.second.size();
    }
    int orderbooks_size = 0;
    for (const auto& pair : orderbooks){
        orderbooks_size += pair.second.size();
    }
    std::cout << orderbooks_size << " l2 messages saved\n";
    std::cout << tickers_size << " ticker messages saved\n";
}


void Coinbase_Socket::handleTicker(const rapidjson::Document& document, std::unordered_map<std::string, std::vector<Ticker_Info>>& tickers){

    // heavily optimize later, but seems fast enough for now
    try {
        uint64_t timestamp = convertTime(document["timestamp"].GetString()); 
        const rapidjson::Value& data = document["events"][0]["tickers"][0];
        std::string product = data["product_id"].GetString();
        const uint64_t price = static_cast<uint64_t>(std::stod(data["price"].GetString()) * precision);
        const uint64_t best_bid = static_cast<uint64_t>(std::stod(data["best_bid"].GetString()) * precision);
        const uint64_t best_ask = static_cast<uint64_t>(std::stod(data["best_ask"].GetString()) * precision);
        const uint64_t best_bid_q = static_cast<uint64_t>(std::stod(data["best_bid_quantity"].GetString()) * precision);
        const uint64_t best_ask_q = static_cast<uint64_t>(std::stod(data["best_ask_quantity"].GetString()) * precision);
        tickers[product].push_back(Ticker_Info(price, timestamp, best_ask, best_bid, best_ask_q, best_bid_q));

    } catch(std::exception &e){
        std::cout << "Could not handle ticker message due to exception: " << e.what() << "\n";
    }
}

void Coinbase_Socket::handleL2(const rapidjson::Document& document, std::unordered_map<std::string, std::vector<Orderbook_Info>>& orderbooks){

    // heavily optimize later, but seems fast enough for now
    try {
        uint64_t timestamp = convertTime(document["timestamp"].GetString()); 
        const rapidjson::Value& event = document["events"][0];
        const std::string type = event["type"].GetString();
        const std::string product = event["product_id"].GetString();
        Orderbook_Info entry = (type == "snapshot")
            ? Orderbook_Info(timestamp)
            : orderbooks[product].back(); 
        for (const auto& update : event["updates"].GetArray()){
            uint64_t price = static_cast<uint64_t>(std::stod(update["price_level"].GetString()) * precision);
            uint64_t q = static_cast<uint64_t>(std::stod(update["new_quantity"].GetString()) * precision);
            if (update["side"] == "bid") entry.bids[price] = q;
            else entry.asks[price]=q;
        }
        orderbooks[product].emplace_back(entry);

    } catch (std::exception &e){
        std::cout << "Could not handle l2 message due to exception: " << e.what() << "\n";
    }



}
