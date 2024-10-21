cmake_minimum_required(VERSION 3.1...3.29)

project(sample VERSION 1.0 
                    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# main 

include_directories(src)

set(CXX_SRCS 
)

# construct main program with toastrack as a dependency
add_executable(main main.cpp)
target_compile_options(main PRIVATE -pthread -std=c++20)
