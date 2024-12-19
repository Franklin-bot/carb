#include "openssl/sha.h"

#include <boost/algorithm/string.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <x86intrin.h>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <openssl/hmac.h>


namespace bi = boost::archive::iterators;

inline std::string sha256(const std::string inputStr)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    const unsigned char* data = (const unsigned char*)inputStr.c_str();
    SHA256(data, inputStr.size(), hash);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

inline std::string HmacSHA512(std::string_view decodedKey, std::string_view msg)
{
    std::array<unsigned char, EVP_MAX_MD_SIZE> hash;
    unsigned int hashLen;

    HMAC(
        EVP_sha512(),
        decodedKey.data(),
        static_cast<int>(decodedKey.size()),
        reinterpret_cast<unsigned char const*>(msg.data()),
        static_cast<int>(msg.size()),
        hash.data(),
        &hashLen
    );

    return std::string{reinterpret_cast<char const*>(hash.data()), hashLen};
}

inline std::string base64_encode(const std::string& data){
    using base64_it =
        bi::base64_from_binary<bi::transform_width<std::string::const_iterator, 6, 8>>;

    auto tmp = std::string(base64_it(data.begin()), base64_it(data.end()));
    return tmp.append((3 - data.size() % 3) % 3, '=');
}

inline std::string base64_decode(const std::string& data){
    using base64_it =
        bi::transform_width<bi::binary_from_base64<std::string::const_iterator>, 8, 6>;

    return boost::algorithm::trim_right_copy_if(
        std::string(base64_it(data.begin()), base64_it(data.end())),
        [](char chr) { return chr == '\0'; }
    );
}
