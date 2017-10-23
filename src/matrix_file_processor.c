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
    // Check the file even exists.
    if (!file_exists(file_name)) {
        fprintf(stderr, "File not found : %s\n", file_name);
        return false;
    }
    // Try to open the file in read mode.
    FILE * file = open_file(file_name, "r");
    if (file == NULL) {
        return false;
    }
    // Begin parsing data.
    bool no_error = true;
    int file_counter = 0;
    char * buffer = malloc(STRING_MAX_SIZE * sizeof(char));
    int buffer_size = STRING_MAX_SIZE;
    fseek(file, file_counter, SEEK_SET);
    // Read first line where dimensions are specified.
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
    // Begin parsing the first line.
    while (no_error && token != NULL) {
        if (i == 0) {
            // First token should be the row keyword.
            if (strcmp(token, "row") != 0) {
                fprintf(stderr, "Invalid input format : Expected row keyword to start the file.\n");
                no_error = false;
            }
        } else if (i == 1) {
            // Second token should be the actual value of the row.
            if (sscanf(token, "%d", &row) != 1 || row < 1) {
                fprintf(stderr, "Invalid row number format : please enter a valid row number. Must be integer and bigger than 0\n");
                no_error = false;
            }
        } else if (i == 2) {
            // Third token should be the col keyword.
            if (strcmp(token, "col") != 0) {
                fprintf(stderr, "Invalid input format : Expected col keyword.\n");
                no_error = false;
            }
        } else if (i == 3) {
            // Fourth token should be the actual value of col.
            if (sscanf(token, "%d", &col) != 1 || col < 1) {
                fprintf(stderr, "Invalid column number format : please enter a valid column number. Must be integer and bigger than 0\n");
                no_error = false;
            }
        } else {
            // Invalid if more tokens are found.
            fprintf(stderr, "ERROR : Invalid input in the first line\n");
            no_error = false;
        }
        token = strtok(NULL, FIRST_LINE_DELIMITER);
        i++;
    }
    // If an error is found, end parsing.
    if (!no_error) {
        free(buffer);
        close_file(file);
        return false;
    }
    // Initialize matrix.
    init_matrix(matrix_read, row, col);
    int matrix_lines_read = 0;
    fseek(file, file_counter, SEEK_SET);
    // Begin parsing matrix elements.
    while(no_error && read_line(&buffer, &buffer_size, file) != NULL) {
        file_counter += strlen(buffer);
        // If matrix isn't full yet.
        if (matrix_lines_read < row) {
            // tokenize the line to get the seperate values.
            token = strtok(buffer, DELIMITER);
            i = 0;
            while (no_error && token != NULL) {
                // Try to convert each token to a long value.
                if (sscanf(token, "%ld", &(matrix_read->matrix_elements[matrix_lines_read][i])) != 1) {
                    fprintf(stderr, "Invalid matrix element format : please enter a valid matrix element at file %s at line %d at column %d\n", file_name,
                    matrix_lines_read + 1, i + 1);
                    no_error = false;
                }
                // Get the next token.
                token = strtok(NULL, DELIMITER);
                i++;
            }
            // If the number of columns isn't equal to the expected number raise error.
            if (no_error && i != col) {
                fprintf(stderr, "Line %d in file %s has wrong number of columns : found %d expected %d...!\n", matrix_lines_read + 1, file_name, i, col);
                no_error = false;
            }
            // Increase number of lines read.
            matrix_lines_read++;
        // Else if full, make sure it is just empty lines.
        } else {
            i = 0;
            while (buffer[i] != '\0') {
                if (buffer[i] != '\n' && buffer[i] != '\t' && buffer[i] != '\r' && buffer[i] != '\f' && buffer[i] != ' ' && buffer[i] != EOF) {
                    matrix_lines_read++;
                    break;
                }
                i++;
            }
        }
        fseek(file, file_counter, SEEK_SET);
    }
    // Free resources.
    free(buffer);
    close_file(file);
    // If more lines are read than matrix rows.
    if (no_error && matrix_lines_read != row) {
        fprintf(stderr, "Invalid rows found in %s :  found %d expected %d ...\n", file_name,  matrix_lines_read, row);
        no_error = false;
    }
    return no_error;
}

// Implementation (Documented in header).
bool write_matrix(MATRIX matrix, const char * file_name) {
    // Try to open/create the file to write to.
    FILE * file = open_file(file_name, "w");
    if (file == NULL) {
        return false;
    }
    // Print some meta-data about the result matrix.
    fprintf(file, "row=%d col=%d\n", matrix.rows, matrix.cols);

    // Print the matrix elements in a suitable format.
    int i = 0, j = 0;
    for (i = 0; i < matrix.rows; i++) {
        for (j = 0; j < matrix.cols; j++) {
            if (j < matrix.cols - 1) {
                fprintf(file, "%ld\t", matrix.matrix_elements[i][j]);
            } else {
                fprintf(file, "%ld", matrix.matrix_elements[i][j]);
            }
        }
        fprintf(file, "\n");
    }
    // Free resources.
    close_file(file);
    return true;
}

// Implementation (Documentation above prototype).
char * read_line(char ** output, int * size, FILE * source) {
    int i = 0;
    // Begin reading characters.
    char c = fgetc(source);
    // If eof reached, just return null.
    if (c == EOF) {
        return NULL;
    }
    // While end of file isn't reached or a new line isn't reached : continue reading.
    while (c != EOF && c != '\n') {
        // Put character in the output string.
        (*output)[i] = c;
        // read next character.
        c = fgetc(source);
        i++;
        // If output string buffer is full, resize it.
        if (i == *size) {
            *size *= 2;
            *output = realloc(*output, *size * sizeof(char));
        }
    }
    // If last character read is a newline, add it to the output.
    if (c != EOF) {
        (*output)[i] = c;
        i++;
        if (i == *size) {
            *size *= 2;
            *output = realloc(*output, *size * sizeof(char));
        }
    }
    // terminate the string.
    (*output)[i] = '\0';
    // Return a points to the read string.
    return *output;
}
