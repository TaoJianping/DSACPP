cmake_minimum_required(VERSION 3.13)
PROJECT(DSACPP_TEST)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(../lib/googletest lib/gtest)
include_directories(../lib/googletest/include)

add_subdirectory(../Src lib/dsa)
include_directories(../Src)

ADD_EXECUTABLE(DSACPP_Test TestVector.h TestVector.cpp)
target_link_libraries(DSACPP_Test gtest_main DSA)