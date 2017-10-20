#include "../include/matrix.h"
#include <stdlib.h>

// Implementation (Documentation in header file).
void init_matrix(MATRIX * uninit_matrix, int row_number, int col_number) {
    // Set matrix row number.
    uninit_matrix->rows = row_number;
    // Set matrix column number.
    uninit_matrix->cols = col_number;
    // allocate memory for the rows in the matrix element.
    uninit_matrix->matrix_elements = malloc(sizeof(long *) * row_number);
    int i = 0;
    for (i = 0; i < row_number; i++) {
        // Allocate memory in each row for the columns.
        uninit_matrix->matrix_elements[i] = malloc(sizeof(long) * col_number);
    }
}

// Implementation (Documentation in header file).
void free_matrix(MATRIX * matrix) {
    if (matrix->matrix_elements != 0) {
        int i = 0;
        for (i = 0; i < matrix->rows; i++) {
            // free memory reserved in each row for the columns.
            if (matrix->matrix_elements[i] != 0) {
                free(matrix->matrix_elements[i]);
            }
        }
        // Free memory taken for the row pointers.
        free(matrix->matrix_elements);
    }
}
