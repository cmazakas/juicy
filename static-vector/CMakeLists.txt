cmake_minimum_required(VERSION 2.8)

project(static-vector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -Wno-unused-parameter -pedantic")

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    )

include_directories("include")
add_subdirectory(include)
add_executable(static-vector ${SOURCE} ${HEADERS})
