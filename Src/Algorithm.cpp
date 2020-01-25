//
// Created by tao on 1/24/20.
//

#include <cstdlib>
#include "Algorithm.h"


void Algorithm::readNumber(const char *str, Stack<float> &opnd) {
    char number = *str;
    opnd.push(static_cast<float> (number) - 48 );
}


float Algorithm::evaluate(char *S, char *&RPN) {
    Stack<float> opnd;
    Stack<char> optr;

    optr.push('\0');

    while (!optr.empty())
    {
        if (isdigit(*S))
        {
            readNumber(S, opnd);
            S++;
            // append(RPN, opnd.top());
        }
        else if (*S == ' ')
        {
            S++;
            continue;
        }
        else
        {
            char order = orderBetween(optr.top(), *S);
            switch (order)
            {
                case '<':
                    optr.push(*S);
                    S++;
                    break;
                case '=':
                    optr.pop();
                    S++;
                    break;
                case '>': {
                    char op = optr.pop();
                    if ('!' == op)
                    {
                        float pOpnd = opnd.pop();
                        exit(-2);
                    }
                    else
                    {
                        auto operand1 = opnd.pop();
                        auto operand2 = opnd.pop();
                        auto res = cal(operand2, op, operand1);
                        opnd.push(res);
                    }
                    break;
                }
                default:
                    exit(-1);
                    break;

            }
        }
    }
    return opnd.pop();
}

float Algorithm::cal(float oprand1, char op, float oprand2) {
    switch (op) {
        case '+':
            return oprand1 + oprand2;
        case '-':
            return oprand1 - oprand2;
        case '*':
            return oprand1 * oprand2;
        case '/':
            return oprand1 / oprand2;
        default:
            exit(-3);
    }
}

char Algorithm::orderBetween(char opor, char s) {
    if (opor == '+')
        opor = ADD;
    else if (opor == '-')
        opor = SUB;
    else if (opor == '*')
        opor = MUL;
    else if (opor == '/')
        opor = DIV;
    else if (opor == '\0')
        opor = EOE;

    if (s == '+') {
        s = ADD;
    } else if (s == '-')
        s = SUB;
    else if (s == '*')
        s = MUL;
    else if (s == '/')
        s = DIV;
    else if (s == '\0')
        s = EOE;

    return pri[opor][s];
}
