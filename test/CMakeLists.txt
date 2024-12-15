# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PriceBufferTest)

# Enable C++17 (or newer)
set(CMAKE_CXX_STANDARD 17)

# Add the source files for your project
add_library(PriceBuffer STATIC
    ../src/engine/price_buf.cpp      # Your implementation file
)

# Add the include directory to the project
target_include_directories(PriceBuffer PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Create the executable for the unit test
add_executable(PriceBufferTest
    test_price_buf.cpp    # Your unit test file
)

# Link the executable with the PriceBuffer library
target_link_libraries(PriceBufferTest PriceBuffer)

# Optionally, enable testing with CTest (if you use a testing framework)
enable_testing()
add_test(NAME PriceBufferTest COMMAND PriceBufferTest)