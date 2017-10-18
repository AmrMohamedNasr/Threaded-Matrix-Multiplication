#ifndef MATRIX_OPERATIONS_H_INCLUDED
#define MATRIX_OPERATIONS_H_INCLUDED

#include "matrix.h"

// Structure containing all the arguments needed for matrix operations.
typedef struct matrix_operations_arguments {
    MATRIX * a;
    MATRIX * b;
    MATRIX * c;
    int a_row;
    int b_col;
} MATRIX_OPERATION_ARGS;

/**
    - Calculates a single element in matrix c from the multiplication of
     a_row from a & b_col from b and storing the result in c[a_row][b_col].
     @args
     - Supposdely a void pointer that will be casted to MATRIX_OPERATION_ARGS object.
**/
void * calculate_element(void * args);

/**
    - Calculates a single row in matrix c from the multiplication of
     a_row from a & all columns from b and storing the result in c[a_row].
     @args
     - Supposdely a void pointer that will be casted to MATRIX_OPERATION_ARGS object.
**/
void * calculate_row(void * args);

#endif // MATRIX_OPERATIONS_H_INCLUDED
