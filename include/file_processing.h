#ifndef FILE_PROCESSING_H_INCLUDED
#define FILE_PROCESSING_H_INCLUDED

#include <stdio.h>
#include <default_values.h>

/**
    - Open the file and return a pointer to it.
    @file_name
    - The file name to open.
    @return
    - A file pointer to the file if it exists, null an error happened during opening it.
    @print
    - Will print to stderr in case of error.
**/
FILE * open_file(char const * file_name);

/**
    - Checks if the file exists.
    @file_name
    - The file name to check if it exists.
    @return
    - Boolean value : true if it exists, false otherwise.
**/
bool file_exists(char const * file_name);

/**
    - Close the file.
    @file
    - The file pointer to close.
    @print
    - Will print to stderr in case of error.
**/
void close_file(FILE * file);

#endif // FILE_PROCESSING_H_INCLUDED
