//
// Created by tao on 1/24/20.
//

#ifndef DSACPP_ALGORITHM_H
#define DSACPP_ALGORITHM_H

#include "Stack.h"



#define N_OPTR 9

typedef enum {
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    FAC,
    L_P,
    R_P,
    EOE,
} Operator;


const char pri[N_OPTR][N_OPTR] = {
        '>', '>', '<', '<', '<', '<', '<', '>', '>',
        '>', '>', '<', '<', '<', '<', '<', '>', '>',
        '>', '>', '>', '>', '<', '<', '<', '>', '>',
        '>', '>', '>', '>', '<', '<', '<', '>', '>',
        '>', '>', '>', '>', '>', '<', '<', '>', '>',
        '>', '>', '>', '>', '>', '>', ' ', '>', '>',
        '<', '<', '<', '<', '<', '<', '<', '=', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        '<', '<', '<', '<', '<', '<', '<', ' ', '=',
};


class Algorithm {
public:
    static float evaluate(char * S, char * &RPN);

private:
    static char orderBetween(char opor, char s);
    static void readNumber(const char * str, Stack<float> & opnd);
    static float cal(float oprand1, char op, float oprand2);
};


#endif //DSACPP_ALGORITHM_H
