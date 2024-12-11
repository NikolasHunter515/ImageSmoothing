cmake_minimum_required(VERSION 3.30)
project(secondtest)

set(CMAKE_CXX_STANDARD 20)

add_executable(secondtest src/main.cpp
        src/imgProcess.h
        src/imgProcessHelp.h
        src/getMedian.h
        src/getMedian.cpp
        src/imgProcessHelp.cpp
        src/imgProcess.cpp
)
