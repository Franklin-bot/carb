#include "scout.hpp"
#include <string>



int main(){

<<<<<<< HEAD
    const std::vector<std::string> products = {"MATIC"};
=======
    // const std::vector<std::string> products = {"ETH"};
    const std::vector<std::string> products = {"MATIC"};
    // const std::vector<std::string> channels = {"ticker", "level2", "heartbeat"};
>>>>>>> 86e50b9 (python analysis)
    const std::vector<std::string> channels = {"ticker", "book"};
    std::unique_ptr<Scout> test = std::make_unique<Scout>(60*5, products);
    test->listenAndNotJudge(60*5);

    return 0;


}

