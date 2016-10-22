cmake_minimum_required(VERSION 2.6)
project(soundcom)

add_executable(soundcom main.cpp)

install(TARGETS soundcom RUNTIME DESTINATION bin)
