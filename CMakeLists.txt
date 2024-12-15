cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Carb CXX)


add_library(COMMON_lib STATIC
    src/common/socket.cpp
)

include_directories(/usr/local/Cellar/boost/1.86.0_2/include)
target_link_libraries(COMMON_lib PRIVATE ${Boost_LIBRARIES})



add_executable(scout_exe src/scout/main.cpp)
target_link_libraries(scout_exe PRIVATE COMMON_lib)


