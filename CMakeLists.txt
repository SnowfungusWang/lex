cmake_minimum_required(VERSION 3.15)
project(lex)

set(CMAKE_CXX_STANDARD 14)

add_executable(lex getTable.cpp anaREs.cpp structs.h re2NFA.cpp NFA2DFA.cpp minDFA.cpp transTable.cpp finalPrgram.cpp)