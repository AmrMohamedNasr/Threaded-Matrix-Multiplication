#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

// Matrix data structure.
typedef struct matrix_struct {
    int rows;
    int cols;
    int ** matrix_elements;
} MATRIX;

/**
    - Initializes and allocates memory for a matrix according to its suitable number of rows and columns.
    @uninit_matrix
    - The pointer to the matrix to allocate memory to, then initialize each component of it.
    @row_number
    - The number of rows in the matrix.
    @col_number
    - The number of columns in the matrix.
**/
void init_matrix(MATRIX * uninit_matrix, int row_number, int col_number);

/**
    - Frees the memory taken by a matrix.
    @matrix
    - A pointer to the matrix to free.
**/
void free_matrix(MATRIX * matrix);
#endif // MATRIX_H_INCLUDED
