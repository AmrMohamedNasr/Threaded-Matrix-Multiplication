#include "../include/matrix_operations.h"
#include <pthread.h>

static MATRIX * input_1;
static MATRIX * input_2;
static MATRIX * output;

// Implementation (Documentation in header).
void set_operation_matrices(MATRIX * a, MATRIX * b, MATRIX * c) {
    input_1 = a;
    input_2 = b;
    output = c;
}

// Implementation (Documentation in header).
void * calculate_element(void * args) {
    // Recast to arguments structure.
    MATRIX_OPERATION_ARGS * op_args = args;
    // Decompress structure to get simpler code.
    int row = op_args->a_row;
    int col = op_args->b_col;
    // Initialize the spot that will be calculated to 0.
    output->matrix_elements[row][col] = 0;
    // Loop over the row and column to calculate the element.
    int i = 0;
    while (i < input_2->rows) {
        output->matrix_elements[row][col] += (input_1->matrix_elements[row][i] * input_2->matrix_elements[i][col]);
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
    int row = op_args->a_row;
    // Loop over the rows and all columns to calculate the output row.
    int i = 0, j = 0;
    while (i < input_2->cols) {
        // reset J.
        j = 0;
        // Initialize the spot that will be calculated to 0.
        output->matrix_elements[row][i] = 0;
        // Complete the multiplication of different elements in the specified row from matrix a and the column i from b.
        while (j < input_2->rows) {
            output->matrix_elements[row][i] += (input_1->matrix_elements[row][j] * input_2->matrix_elements[j][i]);
            j++;
        }
        i++;
    }
    // Exit thread.
    pthread_exit(NULL);
}
