cmake_minimum_required(VERSION 3.20)
project(AhoAlgorithmProject CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_compile_options(/W4 /permissive- /Zc:__cplusplus)
endif()

add_executable(finder main.cpp)
add_executable(tests  test.cpp)
add_executable(bench  bench.cpp)