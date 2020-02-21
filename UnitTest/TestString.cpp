//
// Created by taojianping on 2/11/20.
//

#include "TestString.h"
#include "gtest/gtest.h"
#include "String.h"


TEST(testString, test1) {
    char *test = "CHINCHILLA";
    auto res = String::buildNext(test);
    for (int i = 0; i < 10; ++i) {
        std::cout << *res;
        res++;
    }
}

TEST(testKMP, test1) {
    char T[] = "kmpmpmmkmpkmpmmkmpmkmmmpkmpmmkmpmppp";
    char P[] = "kmpmmkmpm";

    auto index = String::KMP(P, T);
    EXPECT_EQ(index, 10);
}