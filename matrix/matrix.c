#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mtx {
  double *data;
  size_t w, h;
};

/* Dimensions */
size_t matrix_width(const matrix *m) { return m->w; }
size_t matrix_height(const matrix *m) { return m->h; }

matrix *matrix_alloc(size_t w, size_t h) {
  matrix *m = malloc(sizeof(matrix));
  if (!m)
    return NULL;
  m->w = w;
  m->h = h;
  m->data = calloc(w * h, sizeof(double));
  if (!m->data) {
    free(m);
    return NULL;
  }
  return m;
}

matrix *matrix_copy(const matrix *m) {
  matrix *c = matrix_alloc(m->w, m->h);
  if (!c)
    return NULL;
  memcpy(c->data, m->data, m->w * m->h * sizeof(double));
  return c;
}

void matrix_free(matrix *m) {
  if (!m)
    return;
  free(m->data);
  free(m);
}

double *matrix_ptr(matrix *m, size_t i, size_t j) {
  return m->data + i * m->w + j;
}

const double *matrix_cptr(const matrix *m, size_t i, size_t j) {
  return m->data + i * m->w + j;
}

void matrix_set_zero(matrix *m) {
  memset(m->data, 0, m->w * m->h * sizeof(double));
}

void matrix_set_id(matrix *m) {
  matrix_set_zero(m);
  size_t n = m->w < m->h ? m->w : m->h;
  for (size_t i = 0; i < n; ++i) {
    m->data[i * m->w + i] = 1.0;
  }
}

matrix *matrix_alloc_zero(size_t w, size_t h) {
  matrix *m = matrix_alloc(w, h);
  return m; // calloc already zeroed
}
matrix *matrix_alloc_id(size_t w, size_t h) {
  matrix *m = matrix_alloc(w, h);
  if (!m)
    return NULL;
  matrix_set_id(m);
  return m;
}

int matrix_assign(matrix *m1, const matrix *m2) {
  if (m1->w != m2->w || m1->h != m2->h)
    return -1;
  memcpy(m1->data, m2->data, m1->w * m1->h * sizeof(double));
  return 0;
}

int matrix_add(matrix *m1, const matrix *m2) {
  if (m1->w != m2->w || m1->h != m2->h)
    return -1;
  size_t n = m1->w * m1->h;
  for (size_t k = 0; k < n; ++k)
    m1->data[k] += m2->data[k];
  return 0;
}

int matrix_sub(matrix *m1, const matrix *m2) {
  if (m1->w != m2->w || m1->h != m2->h)
    return -1;
  size_t n = m1->w * m1->h;
  for (size_t k = 0; k < n; ++k)
    m1->data[k] -= m2->data[k];
  return 0;
}

void matrix_smul(matrix *m, double d) {
  size_t n = m->w * m->h;
  for (size_t k = 0; k < n; ++k)
    m->data[k] *= d;
}

void matrix_sdiv(matrix *m, double d) { matrix_smul(m, 1.0 / d); }

int matrix_add2(matrix *m, const matrix *m1, const matrix *m2) {
  if (m1->w != m2->w || m1->h != m2->h || m->w != m1->w || m->h != m1->h)
    return -1;
  size_t n = m->w * m->h;
  for (size_t k = 0; k < n; ++k)
    m->data[k] = m1->data[k] + m2->data[k];
  return 0;
}
int matrix_sub2(matrix *m, const matrix *m1, const matrix *m2) {
  if (m1->w != m2->w || m1->h != m2->h || m->w != m1->w || m->h != m1->h)
    return -1;
  size_t n = m->w * m->h;
  for (size_t k = 0; k < n; ++k)
    m->data[k] = m1->data[k] - m2->data[k];
  return 0;
}
int matrix_smul2(matrix *m, const matrix *m1, double d) {
  if (m->w != m1->w || m->h != m1->h)
    return -1;
  size_t n = m->w * m->h;
  for (size_t k = 0; k < n; ++k)
    m->data[k] = m1->data[k] * d;
  return 0;
}
int matrix_sdiv2(matrix *m, const matrix *m1, double d) {
  return matrix_smul2(m, m1, 1.0 / d);
}

int matrix_mul(matrix *m1, const matrix *m2) { return matrix_mul2(m1, m1, m2); }
int matrix_mul2(matrix *m, const matrix *a, const matrix *b) {
  if (a->w != b->h || m->h != a->h || m->w != b->w)
    return -1;
  matrix *tmp = matrix_alloc(m->w, m->h);
  if (!tmp)
    return -1;
  for (size_t i = 0; i < m->h; ++i)
    for (size_t j = 0; j < m->w; ++j) {
      double sum = 0;
      for (size_t k = 0; k < a->w; ++k)
        sum += a->data[i * a->w + k] * b->data[k * b->w + j];
      tmp->data[i * m->w + j] = sum;
    }
  matrix_assign(m, tmp);
  matrix_free(tmp);
  return 0;
}

void matrix_transpose(matrix *m) {
  for (size_t i = 0; i < m->h; ++i)
    for (size_t j = i + 1; j < m->w; ++j) {
      double *p = matrix_ptr(m, i, j);
      double *q = matrix_ptr(m, j, i);
      double t = *p;
      *p = *q;
      *q = t;
    }
}

int matrix_swap_rows(matrix *m, size_t i, size_t j) {
  if (i >= m->h || j >= m->h)
    return -1;
  for (size_t k = 0; k < m->w; ++k) {
    double *p = matrix_ptr(m, i, k);
    double *q = matrix_ptr(m, j, k);
    double t = *p;
    *p = *q;
    *q = t;
  }
  return 0;
}
int matrix_swap_cols(matrix *m, size_t i, size_t j) {
  if (i >= m->w || j >= m->w)
    return -1;
  for (size_t k = 0; k < m->h; ++k) {
    double *p = matrix_ptr(m, k, i);
    double *q = matrix_ptr(m, k, j);
    double t = *p;
    *p = *q;
    *q = t;
  }
  return 0;
}

void matrix_row_smul(matrix *m, size_t i, double d) {
  for (size_t j = 0; j < m->w; ++j)
    *matrix_ptr(m, i, j) *= d;
}

int matrix_row_add(matrix *m, size_t dest, size_t src, double factor) {
  if (dest >= m->h || src >= m->h)
    return -1;
  for (size_t j = 0; j < m->w; ++j)
    *matrix_ptr(m, dest, j) += *matrix_cptr(m, src, j) * factor;
  return 0;
}

double matrix_norm(const matrix *m) {
  double max = 0;
  for (size_t i = 0; i < m->h; ++i) {
    double sum = 0;
    for (size_t j = 0; j < m->w; ++j)
      sum += fabs(*matrix_cptr(m, i, j));
    if (sum > max)
      max = sum;
  }
  return max;
}
