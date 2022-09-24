#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = 0;
  result->rows = rows;
  result->columns = columns;
  if (rows > 0 && columns > 0) {
  result->matrix = calloc(rows, sizeof(double *));
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = calloc(columns, sizeof(double));
    }
    } else {
      err = 1;
      }
      return err;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->columns > 0 && A->rows > 0) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
      }
      free(A->matrix);
      }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int check = 1;
  if (A->columns != B->columns || A->rows != B->rows || A->columns < 1 ||
      A->rows < 1 || B->columns < 1 || B->rows < 1) {
    check = 0;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
          check = 0;
          break;
        }
      }
      if (check == 0) break;
    }
  }
  return check;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
    s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      err = 2;
    }
  } else {
    err = 1;
  }
  return err;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
    s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      err = 2;
    }
  } else {
    err = 1;
  }
  return err;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err = 0;
  if (A->rows > 0 && A->columns > 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
    }
  } else {
    err = 1;
  }
  return err;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (A->rows > 0 && A->columns > 0 && B->columns > 0 && B->rows > 0) {
    if (A->columns == B->rows) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < B->rows; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      err = 2;
    }
  } else {
    err = 1;
  }
  return err;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = 0;
  if (A->rows > 0 && A->columns > 0) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    err = 1;
  }
  return err;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err = 0;
  if (A->rows > 0 && A->columns > 0) {
    if (A->rows != 1 && A->columns != 1) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i1 = 0; i1 < A->rows; i1++) {
        for (int i = 0; i < A->columns; i++) {
          matrix_t res;
          double res_double;
          s21_create_matrix(A->rows - 1, A->columns - 1, &res);
          int k = 0, k1 = 0;
          for (int j = 0; j < res.rows; j++) {
            k = 0;
            if (j >= i1) k1 = 1;
            for (int l = 0; l < res.columns; l++) {
              if (l == i) k = 1;
              res.matrix[j][l] = A->matrix[j + k1][l + k];
            }
          }
          err = s21_determinant(&res, &res_double);
          if (err == 0)
            result->matrix[i1][i] = res_double * ((i + i1) % 2 == 0 ? 1 : -1);
          s21_remove_matrix(&res);
        }
      }
    } else {
      err = 2;
    }
  } else {
    err = 1;
  }
  return err;
}

int s21_determinant(matrix_t *A, double *result) {
  int err = 0;
  if (A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      *result = 0;
      if (A->rows == 2) {
        *result = A->matrix[0][0] * A->matrix[1][1] -
                  A->matrix[0][1] * A->matrix[1][0];
      } else if (A->rows == 1) {
        *result = A->matrix[0][0];
      } else {
        for (int i = 0; i < A->rows; i++) {
          matrix_t res;
          double res_double;
          s21_create_matrix(A->rows - 1, A->rows - 1, &res);
          int k = 0;
          for (int j = 0; j < res.rows; j++) {
            k = 0;
            for (int l = 0; l < res.columns; l++) {
              if (l == i) k = 1;
              res.matrix[j][l] = A->matrix[j + 1][l + k];
            }
          }
          s21_determinant(&res, &res_double);
          s21_remove_matrix(&res);
          *result += A->matrix[0][i] * res_double * (i % 2 == 0 ? 1 : -1);
        }
      }
    } else {
      err = 2;
    }
  } else {
    err = 1;
  }
  return err;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = 0, check = 0;
  if (A->rows > 0 && A->columns > 0) {
    double x;
    int p = s21_determinant(A, &x);
    if (p == 0 && x != 0 && (A->rows != 1 && A->columns != 1)) {
      matrix_t det;
      check = s21_calc_complements(A, &det);
      s21_transpose(&det, result);
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] /= x;
        }
      }
      if (check == 0) s21_remove_matrix(&det);
    } else {
      err = 2;
    }
  } else {
    err = 1;
  }
  return err;
}
