
PROJECT(DSASTRUCT)

SET(LIBDSA_SRC List.h List.cpp vector.h vector.cpp Stack.h Stack.cpp  Algorithm.h Algorithm.cpp BinNode.cpp BinNode.h BinTree.cpp BinTree.h)
add_library(DSA STATIC ${LIBDSA_SRC})