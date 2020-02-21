
PROJECT(DSASTRUCT)

SET(LIBDSA_SRC List.h List.cpp vector.h vector.cpp Stack.h Stack.cpp  Algorithm.h Algorithm.cpp BinNode.cpp BinNode.h BinTree.cpp BinTree.h Graph.cpp Graph.h GraphMatrix.h GraphMatrix.cpp Queue.cpp Queue.h PriorityQueue.cpp PriorityQueue.h PQ_ComplHeap.cpp PQ_ComplHeap.h String.cpp String.h)
add_library(DSA STATIC ${LIBDSA_SRC})