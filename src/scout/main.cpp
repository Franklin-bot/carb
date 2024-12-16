#include "scout.hpp"
#include "../common/socket.hpp"
#include <memory>
#include <iostream>
#include <string>



int main(){

    Socket* test = new Socket(std::string("echo.websocket.org"), 8057);

    return 0;


}
