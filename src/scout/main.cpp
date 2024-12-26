#include "scout.hpp"
#include <string>



int main(){

    const std::vector<std::string> products = {"MATIC"};
    const std::vector<std::string> channels = {"ticker", "book"};
    std::unique_ptr<Scout> test = std::make_unique<Scout>(60*5, products);
    test->listenAndNotJudge(60*1);

    return 0;


}

