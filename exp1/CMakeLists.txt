cmake_minimum_required(VERSION 3.29)
project(dsna_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(dsna_1 main.cpp
        HuffmanTree.cpp
        HuffmanTree.h
        Compress.h
        Compress.cpp)
