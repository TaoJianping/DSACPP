//
// Created by taojianping on 2/9/20.
//

#include "String.h"

int String::KMP(char *P, char *T) {
    int * next = buildNext(P);
    int n = strLen(T);
    int m = strLen(P);
    int i = 0;
    int j = 0;
    while (i < n && j < m) {
        if (T[i] == P[j] || 0 > j) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }

    delete [] next;
    return i - j;
}

int *String::buildNext(char *P) {
    int patternLength = strLen(P);
    int *next = new int[patternLength];
    next[0] = -1;

    int j = 0;
    int t = -1;

    while (j < patternLength - 1) {
        if (t < 0 || P[j] == P[t]) {
            j++;
            t++;
            next[j] = t;
        } else {
            t = next[t];
        }
    }

    return next;
}

int String::strLen(char *S) {
    int ret = 0;
    while (*S != '\0') {
        ret++;
        S++;
    }
    return ret;
}

int *String::buildBC(char *P) {
    int *bc = new int[256];

    for (int j = 0; j < 256; ++j) {
        bc[j] = -1;
    }

    auto patternLength = strLen(P);

    for (int i = 0; i < patternLength; ++i) {
        auto c = P[i];
        bc[c] = i;
    }

    return bc;
}

int *String::buildSS(char *P) {
    int m = strLen(P);
    int * ss = new int[m];
    ss[m-1] = m;
    for (int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0 ; j--) {
        
    }
}


