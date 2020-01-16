project(DSATEST)

include_directories(../Src)

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