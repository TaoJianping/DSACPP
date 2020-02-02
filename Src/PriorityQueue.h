//
// Created by tao on 2/1/20.
//

#ifndef DSACPP_PRIORITYQUEUE_H
#define DSACPP_PRIORITYQUEUE_H


template <typename T> struct PQ {
    virtual void insert(T data) = 0;
    virtual T getMax() = 0;
    virtual T delMax() = 0;
};


#endif //DSACPP_PRIORITYQUEUE_H
