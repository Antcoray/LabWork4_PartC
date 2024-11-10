#include <stdio.h>
#include <stdlib.h>
#include "Task_4.h"

int findMaxSum(int n, int s) {
  int ***array = (int ***)malloc(n * sizeof(int **));
  for (int i = 0; i < n; ++i) {
    array[i] = (int **)malloc(n * sizeof(int *));
    for (int j = 0; j < n; ++j) {
      array[i][j] = (int *)malloc(n * sizeof(int));
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        array[i][j][k] = s;
        ++s;
      }
    }
  }

  int max_sum = 0;
  int sum_main_diag = 0;
  for (int i = 0; i < n; i++) {
    sum_main_diag += array[i][i][i];
  }
  if (sum_main_diag > max_sum) {
    max_sum = sum_main_diag;
  }
  int sum_reverse_diag = 0;
  for (int i = 0; i < n; i++) {
    sum_reverse_diag += array[n - i - 1][i][i];
  }
  if (sum_reverse_diag > max_sum) {
    max_sum = sum_reverse_diag;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 0; ++j) {
      free(array[i][j]);
    }
    free(array[i]);
  }
  free(array);
  return max_sum;
}