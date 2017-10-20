#include "../include/matrix_file_processor.h"
#include "../include/default_values.h"
#include <stdio.h>
#include "../include/file_processing.h"
#include <string.h>
#include <stdlib.h>

#define         FIRST_LINE_DELIMITER           " =\t\n\r\f"
#define         DELIMITER                      " \t\n"

/**
    - Reads a line from a stream. Line ends when EOF or newline are encounted.
    @output
    - Pointer to the string pointer that input will be read into, might get resized during the read operation.
    @size
    - The current size of the string memory.
    @source
    - The stream source to read from.
    @return
    - NULL if EOF is encountered, else return the string pointer.
**/
char * read_line(char ** ouput, int * size, FILE * source);

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
    bool no_error = true;
    int file_counter = 0;
    char * buffer = malloc(STRING_MAX_SIZE * sizeof(char));
    int buffer_size = STRING_MAX_SIZE;
    fseek(file, file_counter, SEEK_SET);
    if (read_line(&buffer, &buffer_size, file) == NULL) {
        fprintf(stderr, "Invalid file format : empty file\n");
        no_error = false;
    }
    if (!no_error) {
        free(buffer);
        close_file(file);
        return false;
    }
    file_counter += strlen(buffer);
    char * token;
    token = strtok(buffer, FIRST_LINE_DELIMITER);
    int i = 0, row , col;
    while (no_error && token != NULL) {
        if (i == 0) {
            if (strcmp(token, "row") != 0) {
                fprintf(stderr, "Invalid input format : Expected row keyword to start the file.\n");
                no_error = false;
            }
        } else if (i == 1) {
            if (sscanf(token, "%d", &row) != 1 || row < 1) {
                fprintf(stderr, "Invalid row number format : please enter a valid row number\n");
                no_error = false;
            }
        } else if (i == 2) {
            if (strcmp(token, "col") != 0) {
                fprintf(stderr, "Invalid input format : Expected col keyword.\n");
                no_error = false;
            }
        } else if (i == 3) {
            if (sscanf(token, "%d", &col) != 1 || col < 1) {
                fprintf(stderr, "Invalid column number format : please enter a valid column number\n");
                no_error = false;
            }
        } else {
            fprintf(stderr, "ERROR : Invalid input in the first line\n");
            no_error = false;
        }
        token = strtok(NULL, FIRST_LINE_DELIMITER);
        i++;
    }
    if (!no_error) {
        free(buffer);
        close_file(file);
        return false;
    }
    init_matrix(matrix_read, row, col);
    int matrix_lines_read = 0;
    fseek(file, file_counter, SEEK_SET);
    while(no_error && read_line(&buffer, &buffer_size, file) != NULL) {
        file_counter += strlen(buffer);
        if (matrix_lines_read < row) {
            token = strtok(buffer, DELIMITER);
            i = 0;
            while (no_error && token != NULL) {
                if (i == col) {
                    fprintf(stderr, "Columns exceed the limit at file %s at line %d\n", file_name,matrix_lines_read + 1);
                    no_error = false;
                }
                if (sscanf(token, "%d", &(matrix_read->matrix_elements[matrix_lines_read][i])) != 1) {
                    fprintf(stderr, "Invalid matrix element format : please enter a valid matrix element at file %s at line %d at column %d\n", file_name,
                    matrix_lines_read + 1, i + 1);
                    no_error = false;
                }
                token = strtok(NULL, DELIMITER);
                i++;
            }
            if (no_error && i != col) {
                fprintf(stderr, "Line %d in file %s has wrong number of columns : found %d expected %d...!\n", matrix_lines_read + 1, file_name, i, col);
                no_error = false;
            }
        }
        matrix_lines_read++;
        fseek(file, file_counter, SEEK_SET);
    }
    free(buffer);
    close_file(file);
    if (no_error && matrix_lines_read != row) {
        fprintf(stderr, "Invalid rows found : found %d expected %d ...\n", matrix_lines_read, row);
        no_error = false;
    }
    return no_error;
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

// Implementation (Documentation above prototype).
char * read_line(char ** output, int * size, FILE * source) {
    int i = 0;
    char c = fgetc(source);
    if (c == EOF) {
        return NULL;
    }
    while (c != EOF && c != '\n') {
        (*output)[i] = c;
        c = fgetc(source);
        i++;
        if (i == *size) {
            *size *= 2;
            *output = realloc(*output, *size * sizeof(char));
        }
    }
    if (c != EOF) {
        (*output)[i] = c;
        i++;
        if (i == *size) {
            *size *= 2;
            *output = realloc(*output, *size * sizeof(char));
        }
    }
    (*output)[i] = '\0';
    return *output;
}
