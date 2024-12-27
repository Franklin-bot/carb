#include "scout.hpp"
#include <string>



int main(int argc, char**argv){

    if (argc != 2){
        std::cout << "invalid arguments\n";
        throw;
    }

    int duration = std::stoi(argv[1]);
    std::cout << "listening for: " << duration << "seconds\n";
    const std::vector<std::string> products = {"MATIC"};
    std::unique_ptr<Scout> test = std::make_unique<Scout>(products);
    test->listenAndNotJudge(duration);

    return 0;


}

