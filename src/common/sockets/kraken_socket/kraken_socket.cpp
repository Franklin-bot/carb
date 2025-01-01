#include "kraken_socket.hpp"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

Kraken_Socket::Kraken_Socket(const std::vector<std::string>& products, const std::vector<std::string>& channels)
    : Socket("ws.kraken.com", 443, "/v2"),
      token(create_token())
{
    websocket::stream_base::timeout opt{
        std::chrono::seconds(3),
        std::chrono::seconds(2),
        false
        };
    ws.set_option(opt);
    std::cout << "connecting(Kraken)\n";
    connect();
    std::cout << "subscribing(Kraken)\n";
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

void Kraken_Socket::subscribe(bool sub, const std::vector<std::string>& p, const std::vector<std::string>& c){

    for (const std::string& channel_id : c){

        rapidjson::Document document;
        document.SetObject();

        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        rapidjson::Value typeValue(sub ? "subscribe" : "unsubscribe", allocator);
        document.AddMember("method", typeValue, allocator);

        rapidjson::Value paramsValue(rapidjson::kObjectType);
        paramsValue.AddMember("channel", rapidjson::Value(channel_id.c_str(), allocator), allocator);
        rapidjson::Value product_ids(rapidjson::kArrayType);
        for (const std::string& product : p){
            product_ids.PushBack(rapidjson::Value(product.c_str(), allocator), allocator);
        }
        paramsValue.AddMember("symbol", product_ids, allocator);

        if (channel_id == "book"){
            paramsValue.AddMember("depth", 500, allocator);
        } else {
            paramsValue.AddMember("event_trigger", "trades", allocator);
        }

        //paramsValue.AddMember("token", rapidjson::Value(token.c_str(), allocator), allocator);
        document.AddMember("params", paramsValue, allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        std::cout << buffer.GetString() << std::endl;
        std::string msg = buffer.GetString();
        write(msg);
    }
}


void Kraken_Socket::listen(int seconds, std::unordered_map<std::string, std::vector<Ticker_Info>>& tickers, 
        std::unordered_map<std::string, std::vector<Orderbook_Update>>& orderbooks){

    std::cout << "Begin Listening\n";
    int l2_count = 0, ticker_count = 0;
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
             } else if (channel == "book"){
                 handleL2(document, orderbooks);
                 l2_count++;
             }
        }
        buffer.clear();

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
    std::cout << orderbooks_size << " l2 updates saved\n";
    std::cout << tickers_size << " ticker updates saved\n";
}


void Kraken_Socket::handleTicker(const rapidjson::Document& document, std::unordered_map<std::string, std::vector<Ticker_Info>>& tickers) const {

    // heavily optimize later, but seems fast enough for now
    try {
        std::string type = document["type"].GetString();
        const rapidjson::Value& data = document["data"][0];
        const std::string& product = data["symbol"].GetString();
        uint64_t price = static_cast<uint64_t>(data["ask"].GetDouble() * precision);
        uint64_t best_bid = static_cast<uint64_t>(data["bid"].GetDouble() * precision);
        uint64_t best_ask = static_cast<uint64_t>(data["ask"].GetDouble() * precision);
        uint64_t best_bid_q = static_cast<uint64_t>(data["bid_qty"].GetDouble() * precision);
        uint64_t best_ask_q = static_cast<uint64_t>(data["ask_qty"].GetDouble() * precision);
        tickers[product].emplace_back(product, 0, price, best_ask, best_bid, best_ask_q, best_bid_q);

    } catch(std::exception &e){
        std::cout << "Could not handle ticker message due to exception: " << e.what() << "\n";
    }

}

void Kraken_Socket::handleL2(const rapidjson::Document& document, std::unordered_map<std::string, std::vector<Orderbook_Update>>& orderbooks) const {
    try {
        const std::string& type = document["type"].GetString();
        const rapidjson::Value& data = document["data"][0];
        const std::string& product = data["symbol"].GetString();

        uint64_t timestamp = (type == "update") ? convertTime(data["timestamp"].GetString()) : 0;

        for (const auto& bid : data["bids"].GetArray()){
            uint64_t price = static_cast<uint64_t>(bid["price"].GetDouble() * precision);
            uint64_t quantity = static_cast<uint64_t>(bid["qty"].GetDouble() * precision);
            orderbooks[product].emplace_back(product, timestamp, "bid", price, quantity);
        }
        for (const auto& ask : data["asks"].GetArray()){
            uint64_t price = static_cast<uint64_t>(ask["price"].GetDouble() * precision);
            uint64_t quantity = static_cast<uint64_t>(ask["qty"].GetDouble() * precision);
            orderbooks[product].emplace_back(product, timestamp, "ask", price, quantity);
        }

    } catch (std::exception &e){
        std::cout << "Could not handle l2 message due to exception: " << e.what() << "\n";
    }

}




