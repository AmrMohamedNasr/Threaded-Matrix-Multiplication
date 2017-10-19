#include "../include/matrix_multiplier.h"
#include "../include/matrix_operations.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/default_values.h"

// Implementation (Documentation in header).
int multiply_threaded_elements(MATRIX * a, MATRIX * b, MATRIX * c) {
    int i = 0, j = 0, created_threads = 0;
    // Get number of elements needed which will be also the number of threads.
    int n = a->rows * b->cols;
    // The number of threads needed.
    pthread_t threads[n];
    // Array of arguments.
    MATRIX_OPERATION_ARGS * args[n];
    // Will hold return value of thread creation.
    int rc;
    // Error check to break out of loop in case of error.
    bool no_error = true;
    // Loop over rows of matrix a.
    for (i = 0; i < a->rows && no_error; i++) {
        // Loop over columns of matrix b.
        for (j = 0; j < b->cols; j++) {
            // Prepare the arguments.
            args[created_threads] = malloc(sizeof(MATRIX_OPERATION_ARGS));
            args[created_threads]->a = a;
            args[created_threads]->b = b;
            args[created_threads]->c = c;
            args[created_threads]->a_row = i;
            args[created_threads]->b_col = j;
            // Create the thread with the suitable method and its arguments.
            rc = pthread_create(&threads[created_threads], NULL, calculate_element, (void *) args[created_threads]);
            // If error during creation, end execution and print warning message.
            if (rc) {
                fprintf(stderr, "ERROR during creation of thread in threaded element method with return code %d\n", rc);
                no_error = false;
                break;
            }
            // Increase the number of created threads if creation is successfull.
            created_threads++;
        }
    }
    // Wait for all threads to end their work.
    for (i = 0; i < created_threads; i++) {
        pthread_join(threads[i], NULL);
        free(args[i]);
    }
    // Return the number of created threads.
    return created_threads;
}

// Implementation (Documentation in header).
int multiply_threaded_rows(MATRIX * a, MATRIX * b, MATRIX * c) {
    int i = 0, created_threads = 0;
    // Number of needed threads is equal to the number of rows of a.
    pthread_t threads[a->rows];
    MATRIX_OPERATION_ARGS * args[a->rows];
    // The return code of thread creation.
    int rc;
    // Loop over the rows of matrix a.
    for (i = 0; i < a->rows; i++) {
        // Prepare the arguments.
        args[created_threads] = malloc(sizeof(MATRIX_OPERATION_ARGS));
        args[created_threads]->a = a;
        args[created_threads]->b = b;
        args[created_threads]->c = c;
        args[created_threads]->a_row = i;
        // create the thread with the right method and send the arguments.
        rc = pthread_create(&threads[created_threads], NULL, calculate_row, (void *) args[created_threads]);
        // If error happened, print message and end execution.
        if (rc) {
            fprintf(stderr, "ERROR during creation of thread with code : %d\n", rc);
            break;
        }
        // Else increment created_threads number.
        created_threads++;
    }
    // Wait for all threads to finish working.
    for (i = 0; i < created_threads; i++) {
        pthread_join(threads[i], NULL);
        free(args[i]);
    }
    // Return the number of created threads.
    return created_threads;
}

// Implementation (Documentation in header).
void multiply_sequentiel(MATRIX * a, MATRIX * b, MATRIX * c) {
    int i = 0, j = 0, k = 0;
    // Loop over rows of a.
    for (i = 0; i < a->rows; i++) {
        // Loop over columns of b.
        for (j = 0; j < b->cols; j++) {
            // Compute multiplication of row i from a and column j from b and store result in c[i][j].
            c->matrix_elements[i][j] = 0;
            for (k = 0; k < b->rows; k++) {
                c->matrix_elements[i][j] += (a->matrix_elements[i][k] * b->matrix_elements[k][j]);
            }
        }
    }
}
