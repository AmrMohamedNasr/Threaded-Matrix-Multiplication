#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix_multiplicator_app.h"
#include "../include/default_values.h"

#include "../include/matrix.h"
#include "../include/matrix_file_processor.h"

int main(int argc, char * argv[])
{
    MATRIX a,b;
    int size = 2000;
    init_matrix(&a, size, size);
    init_matrix(&b, size, size);
    int i = 0, j = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            a.matrix_elements[i][j] = (i + 1) * (j + 1);
            b.matrix_elements[j][i] = (i + 1) * (j + 1);
        }
    }
    write_matrix(a, "a.txt");
    write_matrix(b, "b.txt");
    free_matrix(&a);
    free_matrix(&b);
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

