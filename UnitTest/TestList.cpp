//
// Created by tao on 1/12/20.
//

#include "TestList.h"
#include "gtest/gtest.h"
#include "List.h"

TEST(TestInitList, test1) {
    auto l = new List<int>();
    l->insertAsFirst(1);
    l->insertAsLast(2);
    EXPECT_EQ(l->first()->data, 1);
    EXPECT_EQ(l->first()->succ->data, 2);
}

TEST(TestInit, testInitList) {
    auto l = new List<int> {1, 2, 3, 4, 5};
    EXPECT_EQ(1, l->first()->data);
}

TEST(TestListSearch, test1) {
    auto l = new List<int> {2, 5};
    auto res = l->search(7);
    EXPECT_EQ(res->data, 5);
}

TEST(TestListSearch, test2) {
    auto l = new List<int> {2, 5, 7};
    auto res = l->search(4);
    EXPECT_EQ(res->data, 2);
}

TEST(TestListSearch, test3) {
    auto l = new List<int> {2, 4, 5, 7};
    auto res = l->search(6);
    EXPECT_EQ(res->data, 5);
}

TEST(TestListSearch, test4) {
    auto l = new List<int> {2, 4, 5, 6, 7};
    auto res = l->search(3);
    EXPECT_EQ(res->data, 2);
}

TEST(TestListSelectMax, test1) {
    auto l = new List<int> {2, 4, 5, 6, 7};
    auto res = l->selectMax();
    EXPECT_EQ(res->data, 7);
}

TEST(TestListSelectMax, test2) {
    auto l = new List<int> {1000000, 4, 5, 6, 7};
    auto res = l->selectMax();
    EXPECT_EQ(res->data, 1000000);
}

TEST(TestListInsertionSort, test1) {
    auto l = new List<int> {1000000, 4, 5, 6, 7};
    l->selectionSort();
    EXPECT_EQ(l->first()->data, 4);
    EXPECT_EQ(l->last()->data, 1000000);
}

TEST(TestListInsertionSort, test2) {
    auto l = new List<int> {122, 3, 10, -1, 0};
    l->selectionSort();
    EXPECT_EQ(l->first()->data, -1);
    EXPECT_EQ(l->last()->data, 122);
}