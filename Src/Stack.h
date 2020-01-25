//
// Created by tao on 19-9-15.
//

#ifndef DSACPP_STACK_H
#define DSACPP_STACK_H


#include <cctype>
#include "vector.h"




template<typename T>
class Stack : public Vector<T> {
public:
    T &top() { return (*this)[this->size() - 1]; }

    T pop() {
        return this->remove(this->size() - 1);
    }

    void push(T const &e) { this->insert(this->size(), e); }

};


#endif //DSACPP_STACK_H
