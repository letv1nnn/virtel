# cmake -S . -B build  -  generate the Makefile in build dir
# cmake --build build  -  build the project

cmake_minimum_required(VERSION 3.16)
project(virtel VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS -Wall -Werror)

enable_testing()

add_subdirectory(dependencies/googletest)

add_subdirectory(src)

add_subdirectory(tests)
