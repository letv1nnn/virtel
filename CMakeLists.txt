# cmake -S . -B build to generate the Makefile
# cmake --build build to build the project

cmake_minimum_required(VERSION 3.16)
project(virtel VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(virtel
    src/main.cpp
    src/debug.cpp
    src/runner.cpp
    src/scanner.cpp
    src/token.cpp
)
