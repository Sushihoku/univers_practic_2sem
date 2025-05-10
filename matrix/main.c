
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void print_matrix(const matrix *m) {
  size_t h = matrix_height(m);
  size_t w = matrix_width(m);
  for (size_t i = 0; i < h; ++i) {
    for (size_t j = 0; j < w; ++j)
      printf("%8.3f ", *matrix_cptr(m, i, j));
    printf("\n");
  }
}
matrix *input_matrix() {
  size_t w, h;
  printf("Введите ширину и высоту матрицы: ");
  if (scanf("%zu %zu", &w, &h) != 2)
    return NULL;
  matrix *m = matrix_alloc(w, h);
  if (!m)
    return NULL;
  printf("Введите элементы по строкам (%zu x %zu):\n", h, w);
  for (size_t i = 0; i < h; ++i) {
    for (size_t j = 0; j < w; ++j) {
      scanf("%lf", matrix_ptr(m, i, j));
    }
  }
  return m;
}

int main(void) {
  matrix *A = NULL, *B = NULL, *C = NULL;
  int choice;
  double scalar;

  do {
    printf("1. Ввод матрицы A\n");
    printf("2. Ввод матрицы B\n");
    printf("3. Печать матриц\n");
    printf("4. A + B -> C\n");
    printf("5. A - B -> C\n");
    printf("6. A * scalar -> C\n");
    printf("7. A * B -> C\n");
    printf("8. Транспонирование A\n");
    printf("9. Норма A\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
    if (scanf("%d", &choice) != 1)
      break;

    switch (choice) {
    case 1:
      free(A);
      A = input_matrix();
      break;
    case 2:
      free(B);
      B = input_matrix();
      break;
    case 3:
      if (A) {
        printf("\nMatrix A:\n");
        print_matrix(A);
      }
      if (B) {
        printf("\nMatrix B:\n");
        print_matrix(B);
      }
      if (C) {
        printf("\nMatrix C:\n");
        print_matrix(C);
      }
      break;
    case 4:
      if (A && B) {
        C = matrix_alloc(matrix_width(A), matrix_height(A));
        matrix_add2(C, A, B);
        printf("\nA + B:\n");
        print_matrix(C);
      }
      break;
    case 5:
      if (A && B) {
        C = matrix_alloc(matrix_width(A), matrix_height(A));
        matrix_sub2(C, A, B);
        printf("\nA - B:\n");
        print_matrix(C);
      }
      break;
    case 6:
      if (A) {
        printf("Введите скаляр: ");
        scanf("%lf", &scalar);
        C = matrix_alloc(matrix_width(A), matrix_height(A));
        matrix_smul2(C, A, scalar);
        printf("\nA * %g:\n", scalar);
        print_matrix(C);
      }
      break;
    case 7:
      if (A && B) {
        C = matrix_alloc(matrix_width(B), matrix_height(A));
        matrix_mul2(C, A, B);
        printf("\nA * B:\n");
        print_matrix(C);
      }
      break;
    case 8:
      if (A) {
        matrix_transpose(A);
        printf("\nA^T:\n");
        print_matrix(A);
      }
      break;
    case 9:
      if (A) {
        printf("\nНорма A: %g\n", matrix_norm(A));
      }
      break;
    case 0:
      break;
    default:
      printf("Неверный выбор\n");
    }
  } while (choice != 0);

  matrix_free(A);
  matrix_free(B);
  matrix_free(C);
  return 0;
}
