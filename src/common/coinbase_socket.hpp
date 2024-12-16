#include "socket.hpp"

class Coinbase_Socket : public Socket {
public:

    Coinbase_Socket(std::vector<std::string>& products, std::vector<std::string>& channels);

private:
    std::vector<std::string> products;
    std::vector<std::string> channels;
};
