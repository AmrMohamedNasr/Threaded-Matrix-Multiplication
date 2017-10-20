#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix_multiplicator_app.h"
#include "../include/default_values.h"

#include "../include/matrix_stat_formatter.h"

int main(int argc, char * argv[])
{
    write_stats_square_matrix();
    write_stats_one_row_matrix_a_matching_b_col();
    write_stats_one_column_matrix_a_matching_b_col();
    write_stats_one_column_matrix_a_constant_b_col(50);
    write_stats_one_row_matrix_a_constant_b_col(50);
    // Check number of arguments.
    // If 4 : meaning command and three others. pass them as the file names.
    if (argc == 4) {
        run_matrix_mul_app(argv[1], argv[2], argv[3]);
    // If only command : give the program the default file names.
    } else if (argc == 1) {
        run_matrix_mul_app(DEFAULT_FIRST_MATRIX_FILE, DEFAULT_SECOND_MATRIX_FILE, DEFAULT_OUTPUT_MATRIX_FILE);
    // Otherwise, invalid input.
    } else {
        fprintf(stderr, "Invalid number of arguments\nPlease enter your command either  with no parameters or with\n3 parameters indicating matrix_a file, matrix_b file & output_file\n");
    }
    return 0;
}

