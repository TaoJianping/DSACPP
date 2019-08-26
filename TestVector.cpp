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
    TestBubbleSort();
    return 0;
}

int TestVector::TestCommon() {
    std::cout << "start TestVector" << std::endl;
    // new �����Ķ����ڶ���
    // û�²�Ҫnew
    // TODO ��⿽�����죿������
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

    std::cout << "test TestVector successful" << std::endl;
    return 0;
}

void TestVector::TestRemove() {
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
}

void TestVector::TestBubbleSort() {
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

}
