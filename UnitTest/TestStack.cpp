//
// Created by tao on 1/23/20.
//

#include "TestStack.h"
#include "gtest/gtest.h"
#include "Algorithm.h"


TEST(testReadNumber, test1) {
    Stack<float> testStack;
    char * c = "1 * 2 + 4";
    char * p = "";
    auto res = Algorithm::evaluate(c, p);
    EXPECT_EQ(res, float(6));
}