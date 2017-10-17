#ifndef MATRIX_MULTIPLICATOR_APP_H_INCLUDED
#define MATRIX_MULTIPLICATOR_APP_H_INCLUDED

/**
    - Runs the matrix multiplication problem, reading matrixes from the two input files, multiplying them in both defined methodes and printing
    time taken, threads made for each method on stdout and printing the matrix in the defined output_file with a subscript to signal the method.
    - First method is making a thread for each element in the output matrix.
    - Second method is making a thread for each row in the output matrix.
    @input_file_1
    - The name of the file containing the first matrix.
    @input_file_2
    - The name of the file containing the second matrix.
    @output_file
    - The name of the file to be added to it a subscript and store the output result of matrix_1 * matrix_2.
**/
void run_matrix_mul_app(const char * input_file_1, const char * input_file_2, const char * output_file);

#endif // APP_CORE_H_INCLUDED
