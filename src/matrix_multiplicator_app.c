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
        // Free taken resources if any.
        free_matrix(&a);
        free_matrix(&b);
        return;
    }
    // Make sure it is a valid multiplcation operation.
    if (a.cols != b.rows) {
        fprintf(stderr, "Error in matrixes : first matrix columns must match second matrix rows to be able to multiply them...\nOperation terminated\n");
        // Free taken resources if any.
        free_matrix(&a);
        free_matrix(&b);
        return;
    }
    // Error checking ended for input. Start calculating and generating output.
    init_matrix(&c, a.rows, b.cols);
    int thread_number;
    struct timeval stop, start;
    char temp[STRING_MAX_SIZE];
    double time;

    // Get time , number of threads and result of second method.
    gettimeofday(&start, NULL);
    thread_number = multiply_threaded_rows(&a, &b, &c);
    gettimeofday(&stop, NULL);
    if (thread_number > 0) {
        printf("Number of threads made for <each row computed by a thread>(method 1) : %d\n", thread_number);
    } else {
        printf("Failed to create the threads needed sucessfully --> Operation failed !\n");
        printf("Number of threads made for <each row computed by a thread>(method 1) : %d\n", -thread_number);
    }
    time = (stop.tv_sec - start.tv_sec) + (1e-6) * (stop.tv_usec - start.tv_usec);
    printf("Time taken to compute it in seconds =  %f\n", time);
    // Ready file to write results in.
    add_subscript(output_file, "_1", temp);
    // try to write the result matrix.
    if (!write_matrix(c, temp)) {
        fprintf(stderr, "Error while trying to write the result of row threaded multiplication.\n");
    }
    printf("\n");

    // Get time , number of threads and result of the element-wise threads method.
    gettimeofday(&start, NULL);
    thread_number = multiply_threaded_elements(&a, &b, &c);
    gettimeofday(&stop, NULL);
    if (thread_number > 0) {
        printf("Number of threads made for <each element computed by a thread>(method 2) : %d\n", thread_number);
    } else {
        printf("Failed to create the threads needed sucessfully --> Operation failed !\n");
        printf("Number of threads made for <each element computed by a thread>(method 2) : %d\n", -thread_number);
    }
    time = (stop.tv_sec - start.tv_sec) + (1e-6) * (stop.tv_usec - start.tv_usec);
    printf("Time taken to compute it in seconds =  %f\n", time);
    // Ready file to write results in.
    add_subscript(output_file, "_2", temp);
    // try to write the result matrix.
    if (!write_matrix(c, temp)) {
        fprintf(stderr, "Error while trying to write the result of element threaded multiplication.\n");
    }
    printf("\n");

    /***
    --*---*--               Uncomment this section to calculate results for sequentiel one thread multiplication        --*---*--

    // Get time and result of third method.
    gettimeofday(&start, NULL);
    multiply_sequentiel(&a, &b, &c);
    gettimeofday(&stop, NULL);
    time = (stop.tv_sec - start.tv_sec) + (1e-6) * (stop.tv_usec - start.tv_usec);
    printf("Time taken to compute it in seconds =  %f\n", time);
    // Ready file to write results in.
    add_subscript(output_file, "_3", temp);
    // try to write the result matrix.
    if (!write_matrix(c, temp)) {
        fprintf(stderr, "Error while trying to write the result of sequentiel multiplication.\n");
    }

    ***/
    // Free resources.
    free_matrix(&a);
    free_matrix(&b);
    free_matrix(&c);
}

// Implementation (Documentation above prototype).
void add_subscript(const char * file_name, const char * subscript, char * temp) {
    // Check if it already has an extension.
    char * point = strchr(file_name, '.');
    // If it doesn't, just add the subscript then extension.
    if (point == NULL) {
        // Copy the original file name.
        strcpy(temp, file_name);
        // Add subscript to it.
        strcat(temp, subscript);
        // Add extension.
        strcat(temp, ".txt");
    } else {
    // Otherwise :
        char * last_point;
        char copy [STRING_MAX_SIZE];
        // Copy a backup of the file name.
        strcpy(copy, file_name);
        // Get to the last point in the filename.
        point = strchr(copy, '.');
        while (point != NULL) {
            last_point = point;
            point = strchr(last_point + 1, '.');
        }
        // Terminate string before the last point.
        *(last_point) = '\0';
        // Copy the file name without extension.
        strcpy(temp, copy);
        // Add subscriot.
        strcat(temp, subscript);
        // Add original file extension.
        strcat(temp, ".");
        strcat(temp, last_point + 1);
    }
}
