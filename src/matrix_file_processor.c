#include "../include/matrix_file_processor.h"
#include "../include/default_values.h"
#include <stdio.h>
#include "../include/file_processing.h"
#include <string.h>

#define         FIRST_LINE_DELIMITER           " =\t\n\r\f"
#define         DELIMITER                      " \t\n"
// Implementation (Documented in header).
bool read_matrix(MATRIX * matrix_read, const char * file_name) {
    if (!file_exists(file_name)) {
        fprintf(stderr, "File not found : %s\n", file_name);
        return false;
    }
    FILE * file = open_file(file_name, "r");
    if (file == NULL) {
        return false;
    }
    int file_counter = 0;
    char buffer[STRING_MAX_SIZE];
    fseek(file, file_counter, SEEK_SET);
    if (fgets(buffer, STRING_MAX_SIZE, file) == NULL) {
        fprintf(stderr, "Invalid file format : empty file\n");
        close_file(file);
        return false;
    }
    file_counter += strlen(buffer);
    char * token;
    char copy[STRING_MAX_SIZE];
    strcpy(copy, buffer);
    token = strtok(copy, FIRST_LINE_DELIMITER);
    int i = 0, row , col;
    while (token != NULL) {
        if (i == 0) {
            if (strcmp(token, "row") != 0) {
                fprintf(stderr, "Invalid input format : Expected row keyword to start the file.\n");
                close_file(file);
                return false;
            }
        } else if (i == 1) {
            if (sscanf(token, "%d", &row) != 1 || row < 1) {
                fprintf(stderr, "Invalid row number format : please enter a valid row number\n");
                close_file(file);
                return false;
            }
        } else if (i == 2) {
            if (strcmp(token, "col") != 0) {
                fprintf(stderr, "Invalid input format : Expected col keyword.\n");
                close_file(file);
                return false;
            }
        } else if (i == 3) {
            if (sscanf(token, "%d", &col) != 1 || col < 1) {
                fprintf(stderr, "Invalid column number format : please enter a valid column number\n");
                close_file(file);
                return false;
            }
        } else {
            fprintf(stderr, "ERROR : Invalid input in the first line\n");
        }
        token = strtok(NULL, FIRST_LINE_DELIMITER);
        i++;
    }
    init_matrix(matrix_read, row, col);
    int matrix_lines_read = 0;
    fseek(file, file_counter, SEEK_SET);
    while(fgets(buffer, STRING_MAX_SIZE, file) != NULL) {
        file_counter += strlen(buffer);
        if (matrix_lines_read < row) {
            strcpy(copy, buffer);
            token = strtok(copy, DELIMITER);
            i = 0;
            while (token != NULL) {
                if (i == col) {
                    fprintf(stderr, "Columns exceed the limit at file %s at line %d\n", file_name,matrix_lines_read + 1);
                    close_file(file);
                    return false;
                }
                if (sscanf(token, "%d", &(matrix_read->matrix_elements[matrix_lines_read][i])) != 1) {
                    fprintf(stderr, "Invalid matrix element format : please enter a valid matrix element at file %s at line %d at column %d\n", file_name,
                    matrix_lines_read + 1, i + 1);
                    close_file(file);
                    return false;
                }
                token = strtok(NULL, DELIMITER);
                i++;
            }
            if (i != col) {
                fprintf(stderr, "Line %d in file %s has wrong number of columns : found %d expected %d...!\n", matrix_lines_read + 1, file_name, i, col);
            }
        }
        matrix_lines_read++;
        fseek(file, file_counter, SEEK_SET);
    }
    close_file(file);
    if (matrix_lines_read != row) {
        fprintf(stderr, "Invalid rows found : found %d expected %d ...\n", matrix_lines_read, row);
        return false;
    }
    return true;
}

// Implementation (Documented in header).
bool write_matrix(MATRIX matrix, const char * file_name) {
    FILE * file = open_file(file_name, "w");
    if (file == NULL) {
        return false;
    }
    fprintf(file, "row=%d col=%d\n", matrix.rows, matrix.cols);
    int i = 0, j = 0;
    for (i = 0; i < matrix.rows; i++) {
        for (j = 0; j < matrix.cols; j++) {
            if (j < matrix.cols - 1) {
                fprintf(file, "%d\t", matrix.matrix_elements[i][j]);
            } else {
                fprintf(file, "%d", matrix.matrix_elements[i][j]);
            }
        }
        fprintf(file, "\n");
    }
    close_file(file);
    return true;
}

