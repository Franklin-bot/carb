#include "coinbase_socket.hpp"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

Coinbase_Socket::Coinbase_Socket(std::vector<std::string>& products, std::vector<std::string>& channels) : 
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
    connect();
    subscribe(true, products, channels);
    test();
    close();
}


void Coinbase_Socket::subscribe(bool sub, std::vector<std::string>& p, std::vector<std::string>& c) {

    std::string key_name{std::getenv("COINBASE_API_TOKEN")};
    std::string key_secret{std::getenv("COINBASE_PRIVATE_TOKEN")};

    std::string timestamp = std::to_string(std::time(0));
    std::string message = timestamp + "GET/users/self/verify";

    std::string hmac_key = base64_decode(key_secret);
    std::string signature = this->CalcHmacSHA256(hmac_key, message);
    std::string signature_b64 = base64_encode(signature);

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

    rapidjson::Value signatureValue(signature_b64.c_str(), allocator);
    document.AddMember("signature", signatureValue, allocator);

    rapidjson::Value apiKeyValue(key_name.c_str(), allocator);
    document.AddMember("key", apiKeyValue, allocator);

    document.AddMember("passphrase", rapidjson::Value("", allocator), allocator);
    
    rapidjson::Value timestampValue(timestamp.c_str(), allocator);
    document.AddMember("timestamp", timestampValue, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::cout << buffer.GetString() << std::endl;

    std::string msg = buffer.GetString();
    this->write(msg);

}

std::string Coinbase_Socket::CalcHmacSHA256(std::string_view decodedKey, std::string_view msg){
    std::array<unsigned char, EVP_MAX_MD_SIZE> hash;
    unsigned int hashLen;

    HMAC(
        EVP_sha256(),
        decodedKey.data(),
        static_cast<int>(decodedKey.size()),
        reinterpret_cast<unsigned char const*>(msg.data()),
        static_cast<int>(msg.size()),
        hash.data(),
        &hashLen
    );

    return std::string{reinterpret_cast<char const*>(hash.data()), hashLen};
}
