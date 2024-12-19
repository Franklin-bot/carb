#include "kraken_socket.hpp"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

Kraken_Socket::Kraken_Socket(const std::vector<std::string>& products, const std::vector<std::string>& channels)
    : Socket("ws-auth.kraken.com/v2", 443, "/"),
      products(products),
      channels(channels),
      token(create_token())
{




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

    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    document.AddMember("nonce", rapidjson::Value(nonce), allocator);

    rapidjson::StringBuffer json_buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(json_buffer);
    document.Accept(writer);

    std::cout << json_buffer.GetString() << std::endl;

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
    req.set(http::field::content_type, "application/json");
    req.set(http::field::accept, "application/json");
    req.set(http::field::host, url);
    req.set("API-Key", key_name);
    req.set("API-Sign", signature_b64);
    req.body() = json_buffer.GetString();
    req.prepare_payload();
    std::cout << req << "\n";

    http::write(stream, req);
    beast::flat_buffer http_buffer;
    http::response<http::dynamic_body> res;
    http::read(stream, http_buffer, res);

    // Write the message to standard out
    std::cout << res << std::endl;
    return "";

};
