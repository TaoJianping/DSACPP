
PROJECT(DSASTRUCT)

SET(LIBDSA_SRC List.h List.cpp vector.h vector.cpp)
add_library(DSA STATIC ${LIBDSA_SRC})