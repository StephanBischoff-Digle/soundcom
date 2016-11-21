cmake_minimum_required(VERSION 2.6)
project(soundcom)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Werror -lasound -lfftw3")

set(SOURCE
    ${SOURCE}
    src/main.cpp
    src/dataframe.cpp
    src/device.cpp
    src/psh_modem.cpp
    )
    
set(HEADERS
    ${HEADERS}
    src/dataframe.h
    src/device.h
    src/modem.h
    src/psh_modem.h
    )
    


add_executable(soundcom ${SOURCE} ${HEADERS})

install(TARGETS soundcom RUNTIME DESTINATION bin)
