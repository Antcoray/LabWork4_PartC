#include <stdio.h>
#include <stdlib.h>

void intro() {
  printf("%s",
         "Задание 4. Выполнил Колесников Антон Сергееевич. \n Эта программа "
         "определяет диагональ с наибольшей суммой чисел в трехмерном \n"
         "динамическом масссиве размера n^3\n введите n = 0 чтобы выйти\n");
}

int IntInputN() {
  char answer[256];
  int x = -1;

  printf("%s", "Введите размер массива\n");
  fgets(answer, sizeof(answer), stdin);

  while (sscanf(answer, "%d", &x) != 1) {
    printf("%s", "Некорректный ввод, введите размер массива\n");
    fgets(answer, sizeof(answer), stdin);
  }
  return x;
}

int IntInputx(int i, int j, int k) {
  char answer[256];
  int x = -1;
  printf("Введите элемент массива с индексами [%d][%d][%d]: ", i, j, k);
  fgets(answer, sizeof(answer), stdin);
  while (sscanf(answer, "%d", &x) != 1) {
    printf(
        "Некорректный ввод, введите элемент массива с индексами [%d][%d][%d]: ",
        i, j, k);
    fgets(answer, sizeof(answer), stdin);
  }
  return x;
}

int main() {
  intro();
  int n = -1;

  do {
    n = IntInputN();
    if (n < 0) {
      printf("Некорректный ввод, введите размер массива");
    }
  } while (n < 0);

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
        do {
          array[i][j][k] = IntInputx(i, j, k);
          if (array[i][j][k] < 0) {
            printf(
                "Некорректный ввод, введите элемент массива с индексами "
                "[%d][%d][%d]: ",
                i, j, k);
          }
        } while (array[i][j][k] < 0);
      }
    }
  }

  int max_sum = 0;
  int max_diag_type = -1;
  // Первая диагональ (0 тип) [0][0][0] -> [n-1][n-1][n-1]
  int sum_main_diag = 0;
  for (int i = 0; i < n; i++) {
    sum_main_diag += array[i][i][i];
  }
  if (sum_main_diag > max_sum) {
    max_sum = sum_main_diag;
    max_diag_type = 0;
  }
  // Обратная диагональ (1 тип) [n-1][0][0] -> [0][n-1][n-1]
  int sum_reverse_diag = 0;
  for (int i = 0; i < n; i++) {
    sum_reverse_diag += array[n - i - 1][i][i];
  }
  if (sum_reverse_diag > max_sum) {
    max_sum = sum_reverse_diag;
    max_diag_type = 1;
  }

  printf("Максимальная сумма диагонали: %d\n", max_sum);
  if (max_diag_type == 0) {
    printf(
        "Эта сумма принадлежит главной диагонали [0][0][0] -> [%d][%d][%d]\n",
        n - 1, n - 1, n - 1);
  } else if (max_diag_type == 1) {
    printf(
        "Эта сумма принадлежит обратной диагонали [%d][0][0] -> [0][%d][%d]\n",
        n - 1, n - 1, n - 1);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 0; ++j) {
      free(array[i][j]);
    }
    free(array[i]);
  }
  free(array);
  return 0;
}
