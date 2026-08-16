cmake_minimum_required(VERSION 3.22.1)
project(mycheat)

add_library(mycheat SHARED main.cpp)

target_link_libraries(mycheat
    android
    log
)
