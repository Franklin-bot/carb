#include "scout.hpp"
#include "../common/socket.hpp"
#include <memory>
#include <iostream>
#include <string>



int main(){

    Socket* test = new Socket("echo.websocket.org", 443);

    return 0;


}

