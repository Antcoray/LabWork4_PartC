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

int ***createArray(int n) {
  int ***array = (int ***)malloc(n * sizeof(int ***));
  for (int i = 0; i < n; ++i) {
    array[i] = (int **)malloc(n * sizeof(int *));
    for (int j = 0; j < n; ++j) {
      array[i][j] = (int *)malloc(n * sizeof(int));
    }
  }
  return array;
}

void freeArray(int ***array, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      free(array[i][j]);
    }
    free(array[i]);
  }
  free(array);
}

void calculateMaxDiagonalSum(int ***array, int n) {
  int max_sum = 0;
  int max_diag_type = -1;

  // Первая диагональ (0 тип) [0][0][0] -> [n-1][n-1][n-1]
  int sum_main_diag1 = 0;
  for (int i = 0; i < n; i++) {
    sum_main_diag1 += array[i][i][i];
  }
  if (sum_main_diag1 > max_sum) {
    max_sum = sum_main_diag1;
    max_diag_type = 0;
  }

  // Обратная диагональ (1 тип) [n-1][0][0] -> [0][n-1][n-1]
  int sum_reverse_diag1 = 0;
  for (int i = 0; i < n; i++) {
    sum_reverse_diag1 += array[n - i - 1][i][i];
  }
  if (sum_reverse_diag1 > max_sum) {
    max_sum = sum_reverse_diag1;
    max_diag_type = 1;
  }

  // Главная диагональ (2 тип) [0][0][n-1] -> [n-1][n-1][0]
  int sum_main_diag2 = 0;
  for (int i = 0; i < n; i++) {
    sum_main_diag2 += array[i][i][n - i - 1];
  }
  if (sum_main_diag2 > max_sum) {
    max_sum = sum_main_diag2;
    max_diag_type = 2;
  }

  // Обратная диагональ (3 тип) [n-1][0][n-1] -> [0][n-1][0]
  int sum_reverse_diag3 = 0;
  for (int i = 0; i < n; i++) {
    sum_reverse_diag3 += array[n - i - 1][i][n - i - 1];
  }
  if (sum_reverse_diag3 > max_sum) {
    max_sum = sum_reverse_diag3;
    max_diag_type = 3;
  }

  printf("Максимальная сумма диагонали: %d\n", max_sum);
  switch (max_diag_type) {
    case 0:
      printf("Эта сумма принадлежит диагонали [0][0][0] -> [%d][%d][%d]\n",
             n - 1, n - 1, n - 1);
      break;
    case 1:
      printf("Эта сумма принадлежит диагонали [%d][0][0] -> [0][%d][%d]\n",
             n - 1, n - 1, n - 1);
      break;
    case 2:
      printf("Эта сумма принадлежит диагонали [0][%d][0] -> [%d][0][%d]\n",
             n - 1, n - 1, n - 1);
      break;
    case 3:
      printf("Эта сумма принадлежит диагонали [0][0][%d] -> [%d][%d][0]\n",
             n - 1, n - 1, n - 1);
      break;
  }
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

  int ***array = createArray(n);

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

  calculateMaxDiagonalSum(array, n);
  freeArray(array, n);
  return 0;
}
