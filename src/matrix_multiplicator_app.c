#include "../include/matrix_multiplicator_app.h"
#include "../include/matrix_file_processor.h"
#include "../include/matrix_multiplier.h"
#include <sys/time.h>
#include <string.h>
#include <stdio.h>

/**
    - Adds a subscript string to the file name.
    @file_name
    - The file name/path to add the subscript to.
    @subscript
    - The subscript to add to the file.
    @temp
    - The string containing the result.
**/
void add_subscript(const char * file_name, const char * subscript, char * temp);

// Implementation (Documentation in header).
void run_matrix_mul_app(const char * input_file_1, const char * input_file_2, const char * output_file) {
    MATRIX a, b, c;
    // Initialize matrixes.
    a.matrix_elements = 0;
    b.matrix_elements = 0;
    c.matrix_elements = 0;
    // Read matrixes and stop operation if an error is detected.
    if (!read_matrix(&a, input_file_1) || !read_matrix(&b, input_file_2)) {
        fprintf(stderr, "Error during reading the matrixes : Won't be able to continue operation...\nOperation terminated\n");
        free_matrix(&a);
        free_matrix(&b);
        return;
    }
    // Make sure it is a valid multiplcation operation.
    if (a.cols != b.rows) {
        fprintf(stderr, "Error in matrixes : first matrix columns must match second matrix columns to be able to multiply them...\nOperation terminated\n");
        free_matrix(&a);
        free_matrix(&b);
        return;
    }
    init_matrix(&c, a.rows, b.cols);
    int thread_number;
    struct timeval stop, start;
    char temp[STRING_MAX_SIZE];
    // Get time , number of threads and result of first method.
    gettimeofday(&start, NULL);
    thread_number = multiply_threaded_elements(&a, &b, &c);
    gettimeofday(&stop, NULL);
    printf("Number of threads made for <each element computed by a thread>(method 2) : %d\n", thread_number);
    printf("Time taken to compute it in seconds:microseconds =  %lu:%lu\n", stop.tv_sec - start.tv_sec, stop.tv_usec - start.tv_usec);
    // Ready file to write results in.
    add_subscript(output_file, "_2", temp);
    // try to write the result matrix.
    if (!write_matrix(c, temp)) {
        fprintf(stderr, "Error while trying to write the result of element threaded multiplication.\n");
    }
    printf("\n");
    // Get time , number of threads and result of second method.
    gettimeofday(&start, NULL);
    thread_number = multiply_threaded_rows(&a, &b, &c);
    gettimeofday(&stop, NULL);
    printf("Number of threads made for <each row computed by a thread>(method 1) : %d\n", thread_number);
    printf("Time taken to compute it in seconds:microseconds =  %lu:%lu\n", stop.tv_sec - start.tv_sec, stop.tv_usec - start.tv_usec);
    // Ready file to write results in.
    add_subscript(output_file, "_1", temp);
    // try to write the result matrix.
    if (!write_matrix(c, temp)) {
        fprintf(stderr, "Error while trying to write the result of row threaded multiplication.\n");
    }
    printf("\n");
    // Get time , number of threads and result of third method.
    gettimeofday(&start, NULL);
    multiply_sequentiel(&a, &b, &c);
    gettimeofday(&stop, NULL);
    printf("Time taken to compute it sequentielly in seconds:microseconds =  %lu:%lu\n", stop.tv_sec - start.tv_sec, stop.tv_usec - start.tv_usec);
    // Ready file to write results in.
    add_subscript(output_file, "", temp);
    // try to write the result matrix.
    if (!write_matrix(c, temp)) {
        fprintf(stderr, "Error while trying to write the result of sequentiel multiplication.\n");
    }
    free_matrix(&a);
    free_matrix(&b);
    free_matrix(&c);
}
// Implementation (Documentation in prototype).
void add_subscript(const char * file_name, const char * subscript, char * temp) {
    char * point = strchr(file_name, '.');
    if (point == NULL) {
        strcpy(temp, file_name);
        strcat(temp, subscript);
        strcat(temp, ".txt");
    } else {
        char * last_point;
        char copy [STRING_MAX_SIZE];
        strcpy(copy, file_name);
        point = strchr(copy, '.');
        while (point != NULL) {
            last_point = point;
            point = strchr(last_point + 1, '.');
        }
        *(last_point) = '\0';
        strcpy(temp, copy);
        strcat(temp, subscript);
        strcat(temp, ".");
        strcat(temp, last_point + 1);
    }
}
