#include "kraken_socket.hpp"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

Kraken_Socket::Kraken_Socket(const std::vector<std::string>& products, const std::vector<std::string>& channels)
    : Socket("ws.kraken.com", 443, "/v2"),
      products(products),
      channels(channels),
      token(create_token())
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


std::string Kraken_Socket::create_token(){

    const std::string url = "api.kraken.com";
    const int port = 443;
    const std::string path = "/0/private/GetWebSocketsToken";
    const std::string key_name{std::getenv("KRAKEN_API_TOKEN")};
    const std::string key_secret{std::getenv("KRAKEN_PRIVATE_TOKEN")};

    uint64_t nonce = (std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count());
    std::string nonce_str = std::to_string(nonce);

    std::string POST_data = nonce_str + "nonce=" + nonce_str;
    std::string message = path + sha256(POST_data);
    std::string decoded_secret = base64_decode(key_secret);
    std::string signature = HmacSHA512(decoded_secret, message);
    std::string signature_b64 = base64_encode(signature);

    ssl::stream<beast::tcp_stream> stream(ioc, ctx);
    auto const results = resolver.resolve(url, std::to_string(port));

    if(! SSL_set_tlsext_host_name(stream.native_handle(), url.c_str()))
    {
        beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
        throw beast::system_error{ec};
    }

    beast::get_lowest_layer(stream).connect(results);
    stream.handshake(ssl::stream_base::client);

    // Set up an HTTP request
    http::request<http::string_body> req{http::verb::post, path, 11};
    req.set("API-Key", key_name);
    req.set("API-Sign", signature_b64);
    req.set(http::field::host, url);
    req.set(http::field::content_type, "application/x-www-form-urlencoded");
    req.body() = "nonce=" + nonce_str;
    req.prepare_payload();

    http::write(stream, req);
    beast::flat_buffer http_buffer;
    http::response<http::dynamic_body> res;
    http::read(stream, http_buffer, res);

    rapidjson::Document response;
    response.Parse(beast::buffers_to_string(res.body().data()).c_str());
    return response["result"]["token"].GetString();

};

void Kraken_Socket::subscribe(const bool sub, const std::vector<std::string>& p, const std::vector<std::string>& c){

    for (const std::string& channel_id : c){

        rapidjson::Document document;
        document.SetObject();

        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        rapidjson::Value typeValue(sub ? "subscribe" : "unsubscribe", allocator);
        document.AddMember("event", typeValue, allocator);

        rapidjson::Value paramsValue(rapidjson::kObjectType);
        paramsValue.AddMember("name", rapidjson::Value(channel_id.c_str(), allocator), allocator);
        rapidjson::Value product_ids(rapidjson::kArrayType);
        for (const std::string& product : p){
            product_ids.PushBack(rapidjson::Value(product.c_str(), allocator), allocator);
        }
        document.AddMember("subscription", paramsValue, allocator);
        document.AddMember("pair", product_ids, allocator);
        // document.AddMember("token", rapidjson::Value(token.c_str(), allocator), allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        std::cout << buffer.GetString() << std::endl;
        std::string msg = buffer.GetString();
        write(msg);
    }

    time_t end = time(0) + 5;
    while (time(0) < end) {
        ws.read(buffer);
        std::string message = beast::buffers_to_string(buffer.data());
        std::cout << message << "\n";

        buffer.clear();

    }
}


void Kraken_Socket::listen(int seconds, std::unordered_map<std::string, std::vector<Ticker_Info>>& tickers, 
        std::unordered_map<std::string, std::vector<Orderbook_Info>>& orderbooks){

    std::cout << "Begin Listening\n";
    int l2_count = 0;
    int ticker_count = 0;
    time_t end = time(0) + seconds;

    while (time(0) < end) {
        ws.read(buffer);
        std::string message = beast::buffers_to_string(buffer.data());
        std::cout << message << "\n";

        buffer.clear();

    }
}
