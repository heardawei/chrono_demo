cmake_minimum_required(VERSION 3.0.0)
project(cxx20_chrono VERSION 0.1.0)

# set(CMAKE_C_STANDARD 11)
# set(CMAKE_C_STANDARD_REQUIRED True)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(cxx20_chrono main.cpp)
target_compile_features(cxx20_chrono PRIVATE cxx_std_20)
