//
// Created by taojianping on 2020/1/9.
//

#include "TestVector.h"
#include "List.h"
#include "gtest/gtest.h"
#include "Stack.h"

int add(int a, int b){
    return a+b;
}

TEST(test1, c1){
    auto l = new List<int>;
    l->insertAsLast(0);
    l->insertAsLast(1);
    auto d = l->first()->data;
    EXPECT_EQ(d, add(0,0));
}

TEST(test2, c2) {
    EXPECT_EQ(5, add(3,2));
}