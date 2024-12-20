cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Carb CXX)


find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(RapidJSON REQUIRED)
find_package(jwt-cpp REQUIRED)
find_package(curlpp REQUIRED)
find_package(fmt REQUIRED)

add_library(COMMON_lib OBJECT src/common/kraken_socket.cpp src/common/socket.cpp src/common/coinbase_socket.cpp)
target_link_libraries(COMMON_lib Boost::boost)
target_link_libraries(COMMON_lib ${OPENSSL_LIBRARIES})
target_link_libraries(COMMON_lib rapidjson)
target_link_libraries(COMMON_lib jwt-cpp::jwt-cpp)
target_link_libraries(COMMON_lib curlpp::curlpp)
target_link_libraries(COMMON_lib Boost::json)
target_link_libraries(COMMON_lib fmt::fmt)

add_executable(scout_exe src/scout/main.cpp src/scout/scout.cpp)
target_link_libraries(scout_exe PRIVATE COMMON_lib)


