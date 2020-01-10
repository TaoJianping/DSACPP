cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

SET(LIBDSA_SRC List.h List.cpp vector.h vector.cpp)

add_library(DSA STATIC ${LIBDSA_SRC})