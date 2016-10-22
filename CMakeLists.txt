cmake_minimum_required(VERSION 2.6)
project(soundcom)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -lasound")

set(SOURCE
    ${SOURCE}
    src/main.cpp
    src/dataframe.cpp
    src/device.cpp
    )
    
set(HEADERS
    ${HEADERS}
    src/dataframe.h
    src/device.h
    )

add_executable(soundcom ${SOURCE} ${HEADERS})

install(TARGETS soundcom RUNTIME DESTINATION bin)
