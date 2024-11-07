#include <stdio.h>
#include <stdlib.h>

int correctInputX() {
  char input[50];
  float number;
  int integer;
  char extra;

  printf("Введите значение: ");
  fgets(input, sizeof(input), stdin);
  if (sscanf(input, "%f%c", &number, &extra) == 1) {
    printf("Введено число: %.2f\n", number);
    if ((int)number == number) {
      integer = (int)number;
      printf("Введено целое число: %d\n", integer);
      if (integer >= 0) {
        printf("Введено неотрицательное целое число: %d\n", integer);
      } else {
        printf("Введено отрицательное целое число.\n");
      }
    } else {
      printf("Число является дробным.\n");
    }
  } else {
    printf("Ошибка: введено не число.\n");
  }
  return 0;
}

int main() {
  int n;
  printf("Введите размер массива n: ");
  scanf("%d", &n);

  int *array = (int *)malloc(n * sizeof(int **));
  for (int i = 0; i < n; i++) {
    array[i] = (int **)malloc(n * sizeof(int *));
    for (int j = 0; j < n; j++) {
      array[i][j] = (int *)malloc(n * sizeof(int));
      for (int k = 0; k < n; k++) {
        array[i][j][k] = correctInputX();
      }
    }
  }

  int maxSum = 0;

  int sum1 = 0;
  for (int i = 0; i < n; i++) {
    sum1 += array[i][i][i];
  }
  if (sum1 > maxSum) maxSum = sum1;

  int sum2 = 0;
  for (int i = 0; i < n; i++) {
    sum2 += array[i][i][n - 1 - i];
  }
  if (sum2 > maxSum) maxSum = sum2;

  printf("Максимальная сумма диагонали: %d\n", maxSum);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      free(array[i][j]);
    }
    free(array[i]);
  }
  free(array);

  return 0;
}
