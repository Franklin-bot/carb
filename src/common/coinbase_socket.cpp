#include "coinbase_socket.hpp"



namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

Coinbase_Socket::Coinbase_Socket(std::vector<std::string>& products, std::vector<std::string>& channels) : 
    Socket("ws-feed.exchange.coinbase.com", 443, "/"),
    products(products),
    channels(channels)
{
    std::string pair = "ETH-USD";
    connect();
    subscribe(pair);
    test();
    close();

}

std::string Coinbase_Socket::unsubscripStr(std::string& pair) {
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    document.AddMember("type", rapidjson::Value("unsubscribe", allocator), allocator);

    rapidjson::Value product_ids(rapidjson::kArrayType);
    rapidjson::Value channels(rapidjson::kArrayType);

    rapidjson::Value pairValue;
    pairValue.SetString(pair.c_str(), pair.length(), allocator);
    product_ids.PushBack(pairValue, allocator);

    rapidjson::Value level2Value;
    level2Value.SetString("level2", allocator);
    channels.PushBack(level2Value, allocator);

    rapidjson::Value tickerValue;
    tickerValue.SetString("ticker", allocator);
    channels.PushBack(tickerValue, allocator);

    rapidjson::Value heartbeatValue;
    heartbeatValue.SetString("heartbeat", allocator);
    channels.PushBack(heartbeatValue, allocator);

    document.AddMember("product_ids", product_ids, allocator);
    document.AddMember("channels", channels, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::cout << buffer.GetString() << std::endl;

    return buffer.GetString();
}

std::string Coinbase_Socket::subscripStr(std::string& pair) {
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    document.AddMember("type", rapidjson::Value("subscribe", allocator), allocator);

    rapidjson::Value product_ids(rapidjson::kArrayType);
    rapidjson::Value channels(rapidjson::kArrayType);
    rapidjson::Value ticker(rapidjson::kObjectType);
    rapidjson::Value ticker_product_ids(rapidjson::kArrayType);

    ticker.AddMember("name", "ticker", allocator);

    rapidjson::Value tickerPairValue;
    tickerPairValue.SetString(pair.c_str(), pair.length(), allocator);
    ticker_product_ids.PushBack(tickerPairValue, allocator);
    ticker.AddMember("product_ids", ticker_product_ids, allocator);

    rapidjson::Value pairValue;
    pairValue.SetString(pair.c_str(), pair.length(), allocator);
    product_ids.PushBack(pairValue, allocator);


    rapidjson::Value level2Value;
    level2Value.SetString("level2", allocator);
    channels.PushBack(level2Value, allocator);

    rapidjson::Value heartbeatValue;
    heartbeatValue.SetString("heartbeat", allocator);
    channels.PushBack(heartbeatValue, allocator);

    channels.PushBack(ticker, allocator);


    document.AddMember("product_ids", product_ids, allocator);
    document.AddMember("channels", channels, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::cout << buffer.GetString() << std::endl;

    return buffer.GetString();
}


void Coinbase_Socket::subscribe(std::string& pair) {
    std::string msg = subscripStr(pair);
    write(msg);
}