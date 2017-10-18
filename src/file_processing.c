#include "../include/file_processing.h"
#include <stdio.h>
#include <unistd.h>

// Implementation (Documented in headers).
FILE * open_file(char const * file_name, char const * attr) {
    // Try to open file.
    FILE * file = fopen(file_name, attr);
    // If error occured, print error message.
    if (file == NULL) {
        perror("Error opening file ");
    }
    return file;
}

// Implementation (Documented in headers).
bool file_exists(char const * file_name) {
    // Check if the file exists.
    if (access(file_name, F_OK) == EOF) {
        return false;
    } else {
        return true;
    }
}

// Implementation (Documented in headers).
void close_file(FILE * file) {
    // Try to close file, print error message if there is a problem.
    if (fclose(file) == EOF) {
        perror("Error closing file ");
    }
}
