//
// Created by taojianping on 2019/8/20.
//

#include "TestVector.h"
#include <iostream>
#include <cassert>

using namespace std;

void TestVector::TestCopyFrom() {
    std::cout << "开始测试copyFrom" << std::endl;
    int test[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto v = Vector<int>(test, 3, 8);
    assert(v[0] == 3);
    assert(v[1] == 4);
    assert(v[2] == 5);
    assert(v[3] == 6);
    assert(v[4] == 7);
    std::cout << "测试copyFrom成功" << std::endl;
}

int TestVector::main() {
    TestCommon();
    TestCopyFrom();
    return 0;
}

int TestVector::TestCommon() {
    std::cout << "开始测试TestVector" << std::endl;
    // new 出来的对象都在堆上
    // 没事不要new
    // TODO 理解拷贝构造？？？？
    Vector<int > v;

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

    std::cout << "测试TestVector成功" << std::endl;
    return 0;
}
