//
// Created by taojianping on 2019/8/20.
//

#include "TestVector.h"
#include <iostream>
#include <cassert>

using namespace std;

void TestVector::TestCopyFrom() {
    std::cout << "start test copyFrom" << std::endl;
    int test[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto v = Vector<int>(test, 3, 8);
    assert(v[0] == 3);
    assert(v[1] == 4);
    assert(v[2] == 5);
    assert(v[3] == 6);
    assert(v[4] == 7);
    std::cout << "test copyFrom successful" << std::endl;
}

int TestVector::main() {
    TestCommon();
    TestCopyFrom();
    TestRemove();
    TestSort();
    TestDeduplicate();
    TestTraverse();
    TestUniquify();
    return 0;
}

int TestVector::TestCommon() {
    std::cout << "start TestCommon" << std::endl;
    Vector<int> v;

    v.insert(0, 9);
    assert(v[0] == 9);

    v.insert(0, 4);
    assert(v[0] == 4);
    assert(v[1] == 9);

    v.insert(1, 5);
    assert(v[1] == 5);

    v.put(1, 2);
    assert(v[1] == 2);

    auto t1 = v.get(2);
    assert(t1 == 9);

    v.insert(3, 6);
    assert(v[0] == 4);
    assert(v[1] == 2);
    assert(v[2] == 9);
    assert(v[3] == 6);

    v.insert(1, 7);
    assert(v[0] == 4);
    assert(v[1] == 7);
    assert(v[2] == 2);
    assert(v[3] == 9);
    assert(v[4] == 6);

    auto test2 = v.remove(2);
    assert(test2 == 2);
    assert(v[0] == 4);
    assert(v[1] == 7);
    assert(v[2] == 9);
    assert(v[3] == 6);

    v.insert(1, 3);
    assert(v[0] == 4);
    assert(v[1] == 3);
    assert(v[2] == 7);
    assert(v[3] == 9);
    assert(v[4] == 6);

    v.insert(3, 4);
    assert(v[0] == 4);
    assert(v[1] == 3);
    assert(v[2] == 7);
    assert(v[3] == 4);
    assert(v[4] == 9);
    assert(v[5] == 6);

    auto test3 = v.size();
    assert(test3 == 6);

    auto test4 = v.disordered();
    assert(test4 == 3);

    auto test5 = v.find(9);
    assert(test5 == 4);

    auto test6 = v.find(5);
    assert(test6 == -1);

    v.sort();
    assert(v[0] == 3);
    assert(v[1] == 4);
    assert(v[2] == 4);
    assert(v[3] == 6);
    assert(v[4] == 7);
    assert(v[5] == 9);

    std::cout << "test TestVector successful" << std::endl;
    return 0;
}

void TestVector::TestRemove() {
    std::cout << "start test TestRemove" << std::endl;
    int l[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto v = Vector<int>(l, 0, 10);
    assert(v[0] == 0);
    assert(v[1] == 1);
    assert(v[2] == 2);
    assert(v[3] == 3);
    assert(v[4] == 4);
    assert(v[5] == 5);
    assert(v[6] == 6);
    assert(v[7] == 7);
    assert(v[8] == 8);
    assert(v[9] == 9);

    v.remove(2, 7);

    assert(v[0] == 0);
    assert(v[1] == 1);
    assert(v[2] == 7);
    assert(v[3] == 8);
    assert(v[4] == 9);

    assert(v.size() == 5);
    std::cout << "test TestRemove Successful" << std::endl;
}

void TestVector::TestSort() {
    std::cout << "start test TestBubbleSort" << std::endl;
    int l[5] = {5, 1, 3, 4, 2};
    auto v = Vector<int>(l, 0, 5);
    v.sort();
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    assert(v[3] == 4);
    assert(v[4] == 5);

    int l1[5] = {5};
    auto v1 = Vector<int>(l1, 0, 1);
    v1.sort();
    assert(v1[0] == 5);

    int l2[10] = {5, 1, 3, 4, 2, 100, 83, 92, 43, 10000};
    auto v2 = Vector<int>(l2, 0, 10);
    v2.sort();
    assert(v2[0] == 1);
    assert(v2[1] == 2);
    assert(v2[2] == 3);
    assert(v2[3] == 4);
    assert(v2[4] == 5);
    assert(v2[5] == 43);
    assert(v2[6] == 83);
    assert(v2[7] == 92);
    assert(v2[8] == 100);
    assert(v2[9] == 10000);
    std::cout << "test TestBubbleSort successful" << std::endl;
}

void TestVector::TestDeduplicate() {
    std::cout << "start test deduplicate" << std::endl;
    int l[5] = {5, 1, 3, 5, 2};
    auto v = Vector<int>(l, 0, 5);
    v.deduplicate();
    assert(v[0] == 5);
    assert(v[1] == 1);
    assert(v[2] == 3);
    assert(v[3] == 2);
    assert(v.size() == 4);

    int l1[1] = {5};
    auto v1 = Vector<int>(l1, 0, 1);
    v1.deduplicate();
    assert(v1[0] == 5);
    assert(v1.size() == 1);

    int l2[4] = {5, 5, 5, 5};
    auto v2 = Vector<int>(l2, 0, 4);
    v2.deduplicate();
    assert(v2[0] == 5);
    assert(v2.size() == 1);

    std::cout << "test deduplicate successful" << std::endl;
}

void TestVector::TestTraverse() {
    std::cout << "start test Traverse" << std::endl;

    int l[5] = {5, 1, 3, 5, 2};
    auto v = Vector<int>(l, 0, 5);
    auto func = Increase<int>();
    v.traverse(func);
    assert(v[0] == 6);
    assert(v[1] == 2);
    assert(v[2] == 4);
    assert(v[3] == 6);
    assert(v[4] == 3);

    std::cout << "test Traverse successful" << std::endl;
}

void TestVector::TestUniquify() {
    std::cout << "start test Uniquify" << std::endl;

    int l[5] = {1, 3, 5, 5, 5};
    auto v = Vector<int>(l, 0, 5);
    v.uniquify();
    assert(v[0] == 1);
    assert(v[1] == 3);
    assert(v[2] == 5);
    assert(v.size() == 3);

    int l1[5] = {1, 5, 5, 5, 5};
    auto v1 = Vector<int>(l1, 0, 5);
    v1.uniquify();
    assert(v1[0] == 1);
    assert(v1[1] == 5);
    assert(v1.size() == 2);

    int l2[5] = {1, 5, 5, 10, 10};
    auto v2 = Vector<int>(l2, 0, 5);
    v2.uniquify();
    assert(v2[0] == 1);
    assert(v2[1] == 5);
    assert(v2[2] == 10);
    assert(v2.size() == 3);

    std::cout << "test Uniquify successful" << std::endl;
}
