#include "../include/matrix_stat_formatter.h"
#include <stdio.h>
#include "../include/matrix.h"
#include "../include/file_processing.h"
#include <sys/time.h>
#include "../include/matrix_multiplier.h"

#define         LIMIT           1000

/**
    - Writes a stat line containing the time taken taken for each method, number of rows of a, number of columns of a
    and number of columns of b.
    @file
    - The file to write into the line.
    @a_row
    - The number of rows of matrix a.
    @a_col
    - The number of columns of matrix a.
    @b_row
    - The number of rows of matrix b.
    @b_col
    - The number of columns of matrix b.
**/
void write_stats_line(FILE * file, int a_row, int a_col, int b_row, int b_col);

// Implementation (Documented in headers).
void write_stats_square_matrix() {
    int size = 1;
    FILE * file = open_file("square_stat.txt", "w");
    for (size = 1; size <= LIMIT; size++) {
        write_stats_line(file, size, size, size, size);
    }
    close_file(file);
}

// Implementation (Documented in headers).
void write_stats_one_row_matrix_a_constant_b_col(int b_const_col) {
    int size = 1;
    char temp[STRING_MAX_SIZE];
    sprintf(temp, "%s_%d.txt", "one_row_a_b_col", b_const_col);
    FILE * file = open_file(temp, "w");
    for (size = 1; size <= LIMIT; size++) {
        write_stats_line(file, 1, size, size, b_const_col);
    }
    close_file(file);
}

// Implementation (Documented in headers).
void write_stats_one_column_matrix_a_constant_b_col(int b_const_col) {
    int size = 1;
    char temp[STRING_MAX_SIZE];
    sprintf(temp, "%s_%d.txt", "one_col_a_b_col", b_const_col);
    FILE * file = open_file(temp, "w");
    for (size = 1; size <= LIMIT; size++) {
        write_stats_line(file, size, 1, 1, b_const_col);
    }
    close_file(file);
}

// Implementation (Documented in headers).
void write_stats_one_row_matrix_a_matching_b_col() {
    int size = 1;
    FILE * file = open_file("one_row_a.txt", "w");
    for (size = 1; size <= LIMIT; size++) {
        write_stats_line(file, 1, size, size, size);
    }
    close_file(file);
}

// Implementation (Documented in headers).
void write_stats_one_column_matrix_a_matching_b_col() {
    int size = 1;
    FILE * file = open_file("one_col_a.txt", "w");
    for (size = 1; size <= LIMIT; size++) {
        write_stats_line(file, size, 1, 1, size);
    }
    close_file(file);
}

//Implementation (Documented above prototype).
void write_stats_line(FILE * file, int a_row, int a_col, int b_row, int b_col) {
    // Initialize matrixes.
    MATRIX a,b;
    init_matrix(&a, a_row, a_col);
    init_matrix(&b, b_row, b_col);
    int i = 0, j = 0;
    for (i = 0; i < a.rows; i++) {
        for (j = 0; j < a.cols; j++) {
            a.matrix_elements[i][j] = (i + 1) * (j + 1);
        }
    }
    for (i = 0; i < b.cols; i++) {
        for (j = 0; j < b.rows; j++) {
            b.matrix_elements[j][i] = (i + 1) * (j + 1);
        }
    }
    // Define output matrix
    MATRIX c;
    // Initialize matrix c.
    init_matrix(&c, a.rows, b.cols);
    // Begin calculating.
    int thread_number_row, thread_number_element;
    struct timeval stop, start;
    double time_ele, time_row, time_seq;
    // Get time , number of threads and result of the element-wise threads method.
    gettimeofday(&start, NULL);
    thread_number_element = multiply_threaded_elements(&a, &b, &c);
    gettimeofday(&stop, NULL);
    if (thread_number_element > 0) {
        time_ele = (stop.tv_sec - start.tv_sec) + (1e-6) * (stop.tv_usec - start.tv_usec);
    } else {
        time_ele = 0;
    }
    // Get time , number of threads and result of row-wise thread method.
    gettimeofday(&start, NULL);
    thread_number_row = multiply_threaded_rows(&a, &b, &c);
    gettimeofday(&stop, NULL);
    if (thread_number_row > 0) {
        time_row = (stop.tv_sec - start.tv_sec) + (1e-6) * (stop.tv_usec - start.tv_usec);
    } else {
        time_row = 0;
    }
    // Get time and result of third method.
    gettimeofday(&start, NULL);
    multiply_sequentiel(&a, &b, &c);
    gettimeofday(&stop, NULL);
    time_seq = (stop.tv_sec - start.tv_sec) + (1e-6) * (stop.tv_usec - start.tv_usec);
    fprintf(file, "%d\t%d\t%d\t%f\t%f\t%f", a_row, a_col, b_col, time_seq, time_row, time_ele);
    free_matrix(&a);
    free_matrix(&b);
    free_matrix(&c);
}
