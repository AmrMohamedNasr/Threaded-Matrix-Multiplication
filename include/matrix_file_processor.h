#ifndef MATRIX_FILE_PROCESSOR_H_INCLUDED
#define MATRIX_FILE_PROCESSOR_H_INCLUDED

/**
    - Reads a matrix from a file and saves it in matrix_read.
    @file_name
    - The name of the file containing the matrix.
    @matrix_read
    - The matrix that will store the results.
**/
bool read_matrix(Matrix * matrix_read, const char * file_name);

/**
    - Writes a matrix to a file.
    @file_name
    - The name of the file to write the matrix in.
    @matrix
    - The matrix that will be written in the file.
**/
bool write_matrix(Matrix matrix, const char * file_name);

#endif // MATRIX_FILE_PROCESSOR_H_INCLUDED
