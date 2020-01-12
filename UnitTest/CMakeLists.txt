project(DSATEST)

include(ExternalProject)

ExternalProject_Add(googletest
        GIT_REPOSITORY    https://github.com/google/googletest.git
        GIT_TAG           master
        SOURCE_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/include/gtest"
        BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/lib/gtest"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ""
        INSTALL_COMMAND   ""
        TEST_COMMAND      ""
        )

include_directories(../Src)
add_subdirectory(include/gtest)

set(
        Headers
            TestVector.h
            TestList.h
)

set(
        Sources
            TestVector.cpp
            TestList.cpp
)



ADD_EXECUTABLE(DSACPP_Test ${Headers} ${Sources})
target_link_libraries(DSACPP_Test gtest gtest_main DSA)