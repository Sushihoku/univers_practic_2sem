#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct mtx matrix;

/* Allocation */
matrix *matrix_alloc(size_t w, size_t h);
matrix *matrix_copy(const matrix *m);
void matrix_free(matrix *m);

/* Dimensions */
size_t matrix_width(const matrix *m);
size_t matrix_height(const matrix *m);

/* Element access */
double *matrix_ptr(matrix *m, size_t i, size_t j);
const double *matrix_cptr(const matrix *m, size_t i, size_t j);

/* Initialization */
void matrix_set_zero(matrix *m);
void matrix_set_id(matrix *m);
matrix *matrix_alloc_zero(size_t w, size_t h);
matrix *matrix_alloc_id(size_t w, size_t h);

/* Assignment */
int matrix_assign(matrix *m1, const matrix *m2);

/* Arithmetic operations */
int matrix_add(matrix *m1, const matrix *m2);
int matrix_sub(matrix *m1, const matrix *m2);
void matrix_smul(matrix *m, double d);
void matrix_sdiv(matrix *m, double d);

int matrix_add2(matrix *m, const matrix *m1, const matrix *m2);
int matrix_sub2(matrix *m, const matrix *m1, const matrix *m2);
int matrix_smul2(matrix *m, const matrix *m1, double d);
int matrix_sdiv2(matrix *m, const matrix *m1, double d);

int matrix_mul(matrix *m1, const matrix *m2);
int matrix_mul2(matrix *m, const matrix *m1, const matrix *m2);

/* Manipulations */
void matrix_transpose(matrix *m);
int matrix_swap_rows(matrix *m, size_t i, size_t j);
int matrix_swap_cols(matrix *m, size_t i, size_t j);
void matrix_row_smul(matrix *m, size_t i, double d);
int matrix_row_add(matrix *m, size_t dest, size_t src, double factor);

double matrix_norm(const matrix *m);

/* Exponential */
matrix *matrix_exp(const matrix *A, double eps);

/* Solve AX = B */
matrix *matrix_solve(const matrix *A, const matrix *B);

#endif /* MATRIX_H */
