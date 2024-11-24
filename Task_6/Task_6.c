#include <stdio.h>
#include <stdlib.h>

void intro() {
  printf("%s",
         "Задание 4. Выполнил Колесников Антон Сергееевич. \n Эта программа "
         "генерирует магический квадрат заданного порядка N \n"
         "введите N = 0 чтобы выйти\n");
}

int IntInputN() {
  char answer[256];
  unsigned long int x = -1;

  printf("%s", "Введите порядок квадрата N\n");
  fgets(answer, sizeof(answer), stdin);

  while (sscanf(answer, "%lu", &x) != 1) {
    printf("%s", "Некорректный ввод, введите порядок квадрата N\n");
    fgets(answer, sizeof(answer), stdin);
  }
  return x;
}

// нечетное n
void oddMagicSquare(int n, int **square) {
  int num = 1;
  int i = 0, j = n / 2;

  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      square[x][y] = 0;
    }
  }

  while (num <= n * n) {
    square[i][j] = num++;
    int new_i = (i - 1 + n) % n;
    int new_j = (j + 1) % n;
    if (square[new_i][new_j]) {
      i = (i + 1) % n;
    } else {
      i = new_i;
      j = new_j;
    }
  }
}
// 4n
void doublyEvenMagicSquare(int n, int **square) {
  int num = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      square[i][j] = num++;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if ((i % 4 == j % 4) || ((i % 4 + j % 4) == 3)) {
        square[i][j] = n * n + 1 - square[i][j];
      }
    }
  }
}
// 4n+2
void singlyEvenMagicSquare(int n, int **square) {
  int halfN = n / 2;
  int subSquareSize = halfN * halfN;

  int **subSquare = (int **)malloc(halfN * sizeof(int *));
  for (int i = 0; i < halfN; i++) {
    subSquare[i] = (int *)malloc(halfN * sizeof(int));
  }

  for (int i = 0; i < halfN; i++) {
    for (int j = 0; j < halfN; j++) {
      subSquare[i][j] = 0;
    }
  }

  oddMagicSquare(halfN, subSquare);

  for (int i = 0; i < halfN; i++) {
    for (int j = 0; j < halfN; j++) {
      int val = subSquare[i][j];
      square[i][j] = val;
      square[i + halfN][j] = val + 3 * subSquareSize;
      square[i][j + halfN] = val + 2 * subSquareSize;
      square[i + halfN][j + halfN] = val + subSquareSize;
    }
  }

  int k = (n - 2) / 4;

  if (k != 1) {
    for (int i = 0; i < halfN; i++) {
      for (int j = 0; j < k - 1; j++) {
        int temp = square[i][j];
        square[i][j] = square[i + halfN][j];
        square[i + halfN][j] = temp;
      }
    }

    for (int i = 0; i < halfN; i++) {
      for (int j = n - k + 1; j < n; j++) {
        int temp = square[i][j];
        square[i][j] = square[i + halfN][j];
        square[i + halfN][j] = temp;
      }
    }
  }

  for (int i = 0; i < halfN; i++) {
    if (i == halfN / 2 || i == halfN / 2 + halfN) {
      continue;
    }
    int temp = square[i][k - 1];
    square[i][k - 1] = square[i + halfN][k - 1];
    square[i + halfN][k - 1] = temp;
  }

  int temp = square[k][k + 1 - 1];
  square[k][k + 1 - 1] = square[k + halfN][k + 1 - 1];
  square[k + halfN][k + 1 - 1] = temp;

  for (int i = 0; i < halfN; i++) {
    free(subSquare[i]);
  }
  free(subSquare);
}

void freeSquare(int **square, int n) {
  for (int i = 0; i < n; i++) {
    free(square[i]);
  }
  free(square);
}

int main() {
  intro();
  while (1 == 1) {
    unsigned long int n = -1;
    do {
      n = IntInputN();
      if (n > 4294967295) {
        printf("Некорректный ввод\n");
      }
    } while (n > 4294967295);
    if (n == 0) {
      return 0;
    }
    if (n == 2) {
      printf("NO\n");
      continue;
    }

    int **square = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
      square[i] = (int *)malloc(n * sizeof(int));
      for (int j = 0; j < n; j++) {
        square[i][j] = 0;
      }
    }

    if (n % 2 != 0) {
      oddMagicSquare(n, square);
    } else if (n % 4 == 0) {
      doublyEvenMagicSquare(n, square);
    } else {
      singlyEvenMagicSquare(n, square);
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        printf("%d ", square[i][j]);
      }
      printf("\n");
    }

    freeSquare(square, n);
  }
  return 0;
}