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


std::string Coinbase_Socket::create_jwt() {
    // // Set request parameters
    char* key_name = std::getenv("COINBASE_API_TOKEN");
    char* key_secret = std::getenv("COINBASE_PRIV_TOKEN");
    if (key_name == nullptr || key_secret == nullptr){
        throw std::runtime_error("COINBASE_{API,PRIV}_TOKEN not found");
    }

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

    return std::string("hi");

    // return token;
};