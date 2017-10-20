#ifndef MATRIX_STAT_FORMATTER_H_INCLUDED
#define MATRIX_STAT_FORMATTER_H_INCLUDED

/**
    - Write the time results for all methods from multiplying square matrixes varying in size.
**/
void write_stats_square_matrix();

/**
    - Write the time results for all methods from multiplying one row matrix varying in size with a matrix b columns being a constant.
    @b_const_col
    - Number of columns of matrix b.
**/
void write_stats_one_row_matrix_a_constant_b_col(int b_const_col);

/**
    - Write the time results for all methods from multiplying one column matrix varying in size with a matrix b columns being a constant.
    @b_const_col
    - Number of columns of matrix b.
**/
void write_stats_one_column_matrix_a_constant_b_col(int b_const_col);

/**
    - Write the time results for all methods from multiplying one row matrix varying in size with a matrix b columns being equal to number of columns of matrix a.
**/
void write_stats_one_row_matrix_a_matching_b_col();

/**
    - Write the time results for all methods from multiplying one column matrix varying in size with a matrix b columns being equal to number of rows in matrix a.
**/
void write_stats_one_column_matrix_a_matching_b_col();

#endif // MATRIX_STAT_FORMATTER_H_INCLUDED
