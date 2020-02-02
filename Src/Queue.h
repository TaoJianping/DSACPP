//
// Created by tao on 1/31/20.
//

#ifndef DSACPP_QUEUE_H
#define DSACPP_QUEUE_H

#include "List.h"


template <typename T>
class Queue : public List<T>{
    void enqueue(T const& e) { this->insertAsLast(e);}
    T dequeue() {return this->remove(this->first());}
    T& front() { return this->first()->data;}
};


#endif //DSACPP_QUEUE_H
