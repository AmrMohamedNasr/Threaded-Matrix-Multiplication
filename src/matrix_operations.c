#include "../include/matrix_operations.h"
#include <pthread.h>

// Implementation (Documentation in header).
void * calculate_element(void * args) {
    // Recast to arguments structure.
    MATRIX_OPERATION_ARGS * op_args = args;
    // Decompress structure to get simpler code.
    MATRIX * c = op_args->c;
    MATRIX * a = op_args->a;
    MATRIX * b = op_args->b;
    int row = op_args->a_row;
    int col = op_args->b_col;
    // Initialize the spot that will be calculated to 0.
    c->matrix_elements[row][col] = 0;
    // Loop over the row and column to calculate the element.
    int i = 0;
    while (i < b->rows) {
        c->matrix_elements[row][col] += (a->matrix_elements[row][i] * b->matrix_elements[i][col]);
        i++;
    }
    // Exit thread.
    pthread_exit(NULL);
}

// Implementation (Documentation in header).
void * calculate_row(void * args) {
    // Recast to arguments structure.
    MATRIX_OPERATION_ARGS * op_args = args;
    // Decompress structure to get simpler code.
    MATRIX * c = op_args->c;
    MATRIX * a = op_args->a;
    MATRIX * b = op_args->b;
    int row = op_args->a_row;
    // Loop over the rows and all columns to calculate the output row.
    int i = 0, j = 0;
    while (i < b->cols) {
        // reset J.
        j = 0;
        // Initialize the spot that will be calculated to 0.
        c->matrix_elements[row][i] = 0;
        // Complete the multiplication of different elements in the specified row from matrix a and the column i from b.
        while (j < b->rows) {
            c->matrix_elements[row][i] += (a->matrix_elements[row][j] * b->matrix_elements[j][i]);
            j++;
        }
        i++;
    }
    // Exit thread.
    pthread_exit(NULL);
}
