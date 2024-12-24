#include "scout.hpp"
#include <string>



int main(){

    const std::vector<std::string> products = {"MATIC"};
    const std::vector<std::string> channels = {"ticker", "book"};
    std::unique_ptr<Scout> test = std::make_unique<Scout>(10, products);
    test->listenAndNotJudge(10);

    return 0;


}

