#include "coinbase_socket.hpp"



namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

Coinbase_Socket::Coinbase_Socket(const std::vector<std::string>& products, const std::vector<std::string>& channels) : 
    Socket("advanced-trade-ws.coinbase.com", 443, "/"),
    products(products),
    channels(channels)
{
    websocket::stream_base::timeout opt{
        // handshake timeout
        std::chrono::seconds(3),
        // heartbeat timeout
        std::chrono::seconds(2),
        false
    };
    this->ws->set_option(opt);
    std::cout << "connecting\n";
    connect();
    std::cout << "subscribing\n";
    subscribe(true, this->products, channels);
}


void Coinbase_Socket::subscribe(bool sub, const std::vector<std::string>& p, const std::vector<std::string>& c) {

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

        if (channel_id.compare("level2") == 0){
            std::string token = this->create_jwt();
            rapidjson::Value tokenValue(token.c_str(), allocator);
            document.AddMember("jwt", tokenValue, allocator);
        }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        std::cout << buffer.GetString() << std::endl;

        std::string msg = buffer.GetString();
        this->write(msg);

    }

}


std::string Coinbase_Socket::create_jwt(){

    std::string key_name{std::getenv("COINBASE_API_TOKEN")};
    std::string key_secret{std::getenv("COINBASE_PRIVATE_TOKEN")};
    // std::cout << key_name << std::endl;
    // std::cout << key_secret << std::endl;

    // Generate a random nonce
    unsigned char nonce_raw[16];
    RAND_bytes(nonce_raw, sizeof(nonce_raw));
    std::string nonce(reinterpret_cast<char*>(nonce_raw), sizeof(nonce_raw));

    // Create JWT token
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


void Coinbase_Socket::listen(int seconds, std::unordered_map<std::string, std::vector<Coinbase_Ticker>>& tickers, 
        std::unordered_map<std::string, std::map<uint32_t, uint32_t>>& orderbooks){

    std::cout << "Begin Listening\n";
    int l2_count = 0;
    int ticker_count = 0;
    time_t end = time(0) + seconds;

    while (time(0) < end) {
        this->ws->read(*this->buffer);
        std::string message = beast::buffers_to_string(this->buffer->data());
        rapidjson::Document document;
        document.Parse(message.c_str());

        // heavily optimize this later, remove branching
        if (document.HasMember("channel")){
            //std::string product = document["product_id"].GetString();
            std::string channel = document["channel"].GetString();
             if (channel.compare("ticker") == 0){
                 ticker_count++;
             } else if (channel.compare("l2_data") == 0){
                 l2_count++;
             }
        }
        this->buffer->clear();
        // TODO: handle errors messages here
    }
    std::cout << l2_count << " l2 messages handled\n";
    std::cout << ticker_count << " ticker messages handled\n";
}


void Coinbase_Socket::handleTicker(const rapidjson::Document& document, std::vector<Coinbase_Ticker>& ticker){

    uint32_t price = std::stold(document["price"].GetString())*precision;
    uint64_t timestamp = convertTime(document["event time"].GetString()); 
    ticker.push_back(Coinbase_Ticker(price, timestamp));
}

void Coinbase_Socket::handleL2(const rapidjson::Document& document, std::map<uint32_t, uint32_t>& orderbook){

}

