#include <check.h>

#include "s21_matrix.h"

START_TEST(create_matrix) {
  matrix_t A;
  int A_columns;
  int A_rows;
  int return_value;

  A_columns = -5;
  A_rows = 0;
  return_value = s21_create_matrix(A_rows, A_columns, &A);
  ck_assert_int_eq(return_value, INCORRECT_MATRIX);
}
END_TEST

START_TEST(eq_matrix) {
  matrix_t A;
  matrix_t B;
  int A_columns;
  int A_rows;
  int B_columns;
  int B_rows;

  A_columns = B_columns = 5;
  A_rows = B_rows = 6;
  s21_create_matrix(A_rows, A_columns, &A);
  s21_create_matrix(B_rows, B_columns, &B);
  A.matrix[0][0] = 1;
  B.matrix[0][0] = 2;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  A_columns = 5;
  B_columns = 15;
  A_rows = 6;
  B_rows = 26;
  s21_create_matrix(A_rows, A_columns, &A);
  s21_create_matrix(B_rows, B_columns, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  int A_columns;
  int A_rows;
  int B_columns;
  int B_rows;
  int return_value;

  A_columns = B_columns = 16;
  A_rows = B_rows = 5;
  s21_create_matrix(A_rows, A_columns, &A);
  s21_create_matrix(B_rows, B_columns, &B);
  double x = -5;
  for (int i = 0; i < A_rows; i++) {
    for (int j = 0; j < A_columns; j++) {
      A.matrix[i][j] = x;
      x += 0.373747;
      B.matrix[i][j] = 1;
      x -= 0.169375;
    }
  }
  return_value = s21_sum_matrix(&A, &B, &result);
  if (return_value == OK) {
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        ck_assert_int_eq(result.matrix[i][j], A.matrix[i][j] + B.matrix[i][j]);
      }
    }
  }
  ck_assert_int_eq(return_value, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  int A_columns;
  int A_rows;
  int B_columns;
  int B_rows;
  int return_value;

  A_columns = B_columns = 23;
  A_rows = B_rows = 16;
  s21_create_matrix(A_rows, A_columns, &A);
  s21_create_matrix(B_rows, B_columns, &B);
  int x = -5;
  for (int i = 0; i < A_rows; i++) {
    for (int j = 0; j < A_columns; j++) {
      A.matrix[i][j] = x;
      x += 4.245837;
      B.matrix[i][j] = x++;
      x -= 3.285937;
    }
  }
  return_value = s21_sub_matrix(&A, &B, &result);
  if (return_value == OK) {
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        ck_assert_double_eq_tol(result.matrix[i][j],
                                A.matrix[i][j] - B.matrix[i][j], 1e-7);
      }
    }
  }
  ck_assert_int_eq(return_value, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number) {
  matrix_t A;
  matrix_t result;
  matrix_t check;
  double number;
  int A_columns;
  int A_rows;
  int return_value;

  A_rows = 3;
  A_columns = 3;
  s21_create_matrix(A_rows, A_columns, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  s21_create_matrix(A_rows, A_columns, &check);
  check.matrix[0][0] = 2;
  check.matrix[0][1] = 4;
  check.matrix[0][2] = 6;
  check.matrix[1][0] = 8;
  check.matrix[1][1] = 10;
  check.matrix[1][2] = 12;
  check.matrix[2][0] = 14;
  check.matrix[2][1] = 16;
  check.matrix[2][2] = 18;
  number = 2;
  return_value = s21_mult_number(&A, number, &result);
  for (int i = 0; i < A_rows; i++) {
    for (int j = 0; j < A_columns; j++) {
      ck_assert_double_eq_tol(check.matrix[i][j], result.matrix[i][j], 1e-7);
    }
  }
  ck_assert_int_eq(return_value, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}

START_TEST(mult_matrix) {
  matrix_t A;
  matrix_t B;
  matrix_t result;
  matrix_t check;
  int A_columns;
  int A_rows;
  int B_columns;
  int B_rows;
  int return_value;

  A_columns = B_rows = 3;
  A_rows = B_columns = 2;
  s21_create_matrix(A_rows, A_columns, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = -3;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = -2;
  s21_create_matrix(B_rows, B_columns, &B);
  B.matrix[0][0] = -7;
  B.matrix[0][1] = 5;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = -1;
  B.matrix[2][0] = 4;
  B.matrix[2][1] = 3;
  s21_create_matrix(A_rows, B_columns, &check);
  check.matrix[0][0] = -16;
  check.matrix[0][1] = 16;
  check.matrix[1][0] = -35;
  check.matrix[1][1] = 15;
  return_value = s21_mult_matrix(&A, &B, &result);
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq_tol(check.matrix[i][j], result.matrix[i][j], 1e-7);
    }
  }
  ck_assert_int_eq(return_value, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(transponse) {
  matrix_t A;
  matrix_t result;
  matrix_t check;
  int A_columns;
  int A_rows;
  int return_value;

  A_rows = 3;
  A_columns = 2;
  s21_create_matrix(A_rows, A_columns, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  s21_create_matrix(A_columns, A_rows, &check);
  check.matrix[0][0] = 1;
  check.matrix[0][1] = 2;
  check.matrix[0][2] = 3;
  check.matrix[1][0] = 4;
  check.matrix[1][1] = 5;
  check.matrix[1][2] = 6;
  return_value = s21_transpose(&A, &result);
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq_tol(check.matrix[i][j], result.matrix[i][j], 1e-7);
    }
  }
  ck_assert_int_eq(return_value, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}

START_TEST(determinant) {
  matrix_t A;
  double check;
  double result;
  int A_columns;
  int A_rows;
  int return_value;

  A_rows = A_columns = 3;
  s21_create_matrix(A_rows, A_columns, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = -2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = -7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  check = 204;
  return_value = s21_determinant(&A, &result);
  ck_assert_double_eq_tol(result, check, 1e-7);
  ck_assert_int_eq(return_value, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements) {
  matrix_t A;
  matrix_t check;
  matrix_t result;
  int A_columns;
  int A_rows;
  int return_value;

  A_rows = A_columns = 3;
  s21_create_matrix(A_rows, A_columns, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  s21_create_matrix(A_rows, A_columns, &check);
  check.matrix[0][0] = 0;
  check.matrix[0][1] = 10;
  check.matrix[0][2] = -20;
  check.matrix[1][0] = 4;
  check.matrix[1][1] = -14;
  check.matrix[1][2] = 8;
  check.matrix[2][0] = -8;
  check.matrix[2][1] = -2;
  check.matrix[2][2] = 4;
  return_value = s21_calc_complements(&A, &result);
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], check.matrix[i][j], 1e-7);
    }
  }
  ck_assert_int_eq(return_value, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(inverse_matrix) {
  matrix_t A, result, check;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = -1.;
  A.matrix[0][2] = 1.;
  A.matrix[1][0] = -38.;
  A.matrix[1][1] = 41.;
  A.matrix[1][2] = -34.;
  A.matrix[2][0] = 27.;
  A.matrix[2][1] = -29.;
  A.matrix[2][2] = 24.;

  check.matrix[0][0] = 2.;
  check.matrix[0][1] = 5.;
  check.matrix[0][2] = 7.;
  check.matrix[1][0] = 6.;
  check.matrix[1][1] = 3.;
  check.matrix[1][2] = 4.;
  check.matrix[2][0] = 5.;
  check.matrix[2][1] = -2.;
  check.matrix[2][2] = -3.;

  s21_inverse_matrix(&A, &result);
  int res = s21_eq_matrix(&result, &check);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *s21_test = tcase_create("Test");
  SRunner *sr = srunner_create(s1);
  suite_add_tcase(s1, s21_test);

  tcase_add_test(s21_test, create_matrix);
  tcase_add_test(s21_test, eq_matrix);
  tcase_add_test(s21_test, sum_matrix);
  tcase_add_test(s21_test, sub_matrix);
  tcase_add_test(s21_test, mult_number);
  tcase_add_test(s21_test, mult_matrix);
  tcase_add_test(s21_test, transponse);
  tcase_add_test(s21_test, determinant);
  tcase_add_test(s21_test, calc_complements);
  tcase_add_test(s21_test, inverse_matrix);

  srunner_run_all(sr, CK_VERBOSE);
  int errors = srunner_ntests_failed(sr);
  srunner_free(sr);

  return errors == 0 ? 0 : 1;
}
