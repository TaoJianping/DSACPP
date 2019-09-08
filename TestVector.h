//
// Created by taojianping on 2019/8/20.
//

#ifndef DSACPP_TESTVECTOR_H
#define DSACPP_TESTVECTOR_H

#include "vector.h"


class TestVector {
public:
    static int main();
    static int TestCommon();
    static void TestCopyFrom();
    static void TestRemove();
    static void TestSort();
    static void TestDeduplicate();
    static void TestTraverse();
};


template <typename T>
struct Increase {
    // Todo why add this key word -> virtual
    virtual void operator()(T & e) {e++;}
};

#endif //DSACPP_TESTVECTOR_H
