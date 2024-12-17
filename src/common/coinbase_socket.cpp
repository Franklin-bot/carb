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
    subscribe(true, products, channels);
    test();
    close();

}

void Coinbase_Socket::subscribe(bool sub, std::vector<std::string>& p, std::vector<std::string>& c) {
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    rapidjson::Value typeValue(sub ? "subscribe" : "unsubscribe", allocator);
    document.AddMember("type", typeValue, allocator);

    rapidjson::Value product_ids(rapidjson::kArrayType);
    rapidjson::Value channels(rapidjson::kArrayType);

    for (std::string& product : p){
        product_ids.PushBack(rapidjson::Value(product.c_str(), allocator), allocator);
    }
    document.AddMember("product_ids", product_ids, allocator);

    for (std::string& channel : c){
        channels.PushBack(rapidjson::Value(channel.c_str(), allocator), allocator);
    }
    document.AddMember("channels", channels, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::cout << buffer.GetString() << std::endl;

    std::string msg = buffer.GetString();
    this->write(msg);
}

