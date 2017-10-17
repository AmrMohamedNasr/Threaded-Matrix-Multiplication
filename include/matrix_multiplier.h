#ifndef MATRIX_MULTIPLIER_H_INCLUDED
#define MATRIX_MULTIPLIER_H_INCLUDED

/**
    - Multiply a and b and store result in c.
    - Calculate each element in c in a seperate thread.
    @a
    - The first matrix.
    @b
    - The second matrix.
    @c
    - The output matrix.
    @return
    - The number of threads used.
    @print
    - On stderr if an error happens during the creation of a thread.
**/
int multiply_threaded_elements(MATRIX a, MATRIX b, MATRIX * c);

/**
    - Multiply a and b and store result in c.
    - Calculate each row in c in a seperate thread.
    @a
    - The first matrix.
    @b
    - The second matrix.
    @c
    - The output matrix.
    @return
    - The number of threads used.
    @print
    - On stderr if an error happens during the creation of a thread.
**/
int multiply_threaded_rows(MATRIX a, MATRIX b, MATRIX * c);

/**
    - Multiply a and b and store result in c.
    - Calculate all sequentielly in the same thread.
    @a
    - The first matrix.
    @b
    - The second matrix.
    @c
    - The output matrix.
**/
void multiply_sequentiel(MATRIX a, MATRIX b, MATRIX * c);

#endif // MATRIX_MULTIPLIER_H_INCLUDED
