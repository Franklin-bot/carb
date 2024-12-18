#include "scout.hpp"
#include <string>



int main(){

    const std::vector<std::string> products = {"ETH-EUR", "ETH-USD"};
    std::unique_ptr<Scout> test = std::make_unique<Scout>(products);
    return 0;


}

