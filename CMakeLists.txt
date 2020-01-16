cmake_minimum_required(VERSION 3.13)
project(dsacpp)

set(CMAKE_CXX_STANDARD 17)

include(cmake/third_party_import.cmake)

set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(Src)
add_subdirectory(UnitTest)
