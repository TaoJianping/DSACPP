//
// Created by taojianping on 2/9/20.
//

#ifndef DSACPP_STRING_H
#define DSACPP_STRING_H


class String {
public:
    static int KMP(char * P, char * T);
    static int * buildNext(char * P);

    static int BM(char *P, char *T);
    static int *buildBC(char *P);
    static int* buildSS(char* P);

private:
    static int strLen(char *S);
};


#endif //DSACPP_STRING_H
