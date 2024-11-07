#include <stdio.h>
#include <stdlib.h>

void printSquare(int **square, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%2d ", square[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int n;
  printf("Введите размер магического квадрата (нечётное число): ");
  scanf("%d", &n);

  if (n % 2 == 0) {
    printf("Размер должен быть нечётным.\n");
    return 1;
  }

  int square = (int)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    square[i] = (int *)calloc(n, sizeof(int));
  }

  int num = 1;
  int i = 0, j = n / 2;

  while (num <= n * n) {
    square[i][j] = num++;
    int newi = (i - 1 + n) % n;
    int newj = (j + 1) % n;
    if (square[newi][newj] != 0) {
      i = (i + 1) % n;
    } else {
      i = newi;
      j = newj;
    }
  }

  printSquare(square, n);

  for (int i = 0; i < n; i++) {
    free(square[i]);
  }
  free(square);

  return 0;
}