project(DSATEST)

include_directories(../Src)

set(
        Headers
            TestVector.h
            TestList.h
            TestStack.h
)

set(
        Sources
            TestVector.cpp
            TestList.cpp
            TestStack.cpp
        TestString.cpp TestString.h)



ADD_EXECUTABLE(DSACPP_Test ${Headers} ${Sources})
target_link_libraries(DSACPP_Test gtest gtest_main DSA)