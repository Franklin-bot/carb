#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <json/json.h> // For JSON parsing. Requires a JSON library.
#include <curl/curl.h> // For URL encoding. Requires libcurl.

std::string sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string hmac_sha512(const std::string& key, const std::string& message) {
    unsigned char* result;
    unsigned int len = SHA512_DIGEST_LENGTH;
    result = (unsigned char*)malloc(sizeof(char) * len);

    HMAC_CTX* ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, key.c_str(), key.length(), EVP_sha512(), NULL);
    HMAC_Update(ctx, reinterpret_cast<const unsigned char*>(message.c_str()), message.length());
    HMAC_Final(ctx, result, &len);

    std::string hmac_result = std::string(reinterpret_cast<char*>(result), len);

    HMAC_CTX_free(ctx);
    free(result);

    return hmac_result;
}

std::string base64_decode(const std::string& encoded) {
    BIO* bio = BIO_new_mem_buf(encoded.c_str(), -1);
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);

    std::string decoded;
    decoded.resize(encoded.size());
    int decoded_length = BIO_read(bio, &decoded[0], encoded.size());
    decoded.resize(decoded_length);

    BIO_free_all(bio);
    return decoded;
}

std::string url_encode(const std::map<std::string, std::string>& data) {
    std::ostringstream oss;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it != data.begin()) {
            oss << "&";
        }
        oss << curl_easy_escape(nullptr, it->first.c_str(), 0) << "="
            << curl_easy_escape(nullptr, it->second.c_str(), 0);
    }
    return oss.str();
}

std::string getKrakenSignature(const std::string& urlpath, const std::string& data, const std::string& secret) {
    std::string encoded;
    Json::Value jsonData;
    Json::CharReaderBuilder reader;
    std::string errs;

    std::istringstream s(data);
    if (Json::parseFromStream(reader, s, &jsonData, &errs)) {
        std::string nonce = jsonData["nonce"].asString();
        encoded = nonce + data;
    } else {
        // Assuming "data" is a map-like structure for non-JSON inputs
        std::map<std::string, std::string> dataMap; // You would need to populate this map
        encoded = dataMap["nonce"] + url_encode(dataMap);
    }

    std::string sha256Hash = sha256(encoded);
    std::string message = urlpath + sha256Hash;

    std::string decodedSecret = base64_decode(secret);
    std::string hmacDigest = hmac_sha512(decodedSecret, message);

    return hmacDigest;
}

int main() {
    std::string urlpath = "/api/v1/some_endpoint";
    std::string data = "{\"nonce\": \"12345\", \"key\": \"value\"}";
    std::string secret = "your_base64_encoded_secret";

    std::string signature = getKrakenSignature(urlpath, data, secret);
    std::cout << "Signature: " << signature << std::endl;

    return 0;
}
