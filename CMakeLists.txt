cmake_minimum_required(VERSION 3.15)
project(lex)

set(CMAKE_CXX_STANDARD 14)

add_executable(lex main.cpp anaREs.cpp structs.h re2NFA.cpp)