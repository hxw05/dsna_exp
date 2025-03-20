cmake_minimum_required(VERSION 3.29)
project(dsna_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(dsna_2 main.cpp
        Graph.cpp
        Graph.h
        global.h
        test.h
        Files.cpp
        EVFiles.h
        test.cpp
        Functions.cpp
        Functions.h
)
