#include <stdio.h>
#include <stdlib.h>

void intro() {
  printf("%s",
         "Задание 5. Выполнил Колесников Антон Сергееевич. \n Эта программа "
         "создает поле из игры сапер размера n*m символов\n"
         "введите n = 0 или m = 0 чтобы выйти\n");
}

int IntInputN() {
  char answer[256];
  int x = -1;

  printf("%s", "Введите размер поля n\n");
  fgets(answer, sizeof(answer), stdin);

  while (sscanf(answer, "%d", &x) != 1) {
    printf("%s", "Некорректный ввод, введите размеры поля\n");
    fgets(answer, sizeof(answer), stdin);
  }
  return x;
}

int IntInputM() {
  char answer[256];
  int x = -1;

  printf("%s", "Введите размер поля m\n");
  fgets(answer, sizeof(answer), stdin);

  while (sscanf(answer, "%d", &x) != 1) {
    printf("%s", "Некорректный ввод, введите размеры поля\n");
    fgets(answer, sizeof(answer), stdin);
  }
  return x;
}

char **allocateField(int n, int m) {
  char **field = (char **)malloc(n * sizeof(char *));
  for (int i = 0; i < n; i++) {
    field[i] = (char *)malloc(m * sizeof(char));
  }
  return field;
}

void freeField(char **field, int n) {
  for (int i = 0; i < n; i++) {
    free(field[i]);
  }
  free(field);
}

int countMines(char **field, int n, int m, int i, int j) {
  int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int count = 0;
  for (int d = 0; d < 8; d++) {
    int ni = i + dx[d];
    int nj = j + dy[d];
    if (ni >= 0 && ni < n && nj >= 0 && nj < m && field[ni][nj] == '*') {
      count++;
    }
  }
  return count;
}

void printField(char **field, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%c ", field[i][j]);
    }
    printf("\n");
  }
}

int main() {
  intro();
  while (1 == 1) {
    int n, m;
    n = IntInputN();
    if (n == 0) {
      break;
    }
    m = IntInputM();
    if (m == 0) {
      break;
    }

    char **field = allocateField(n, m);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        field[i][j] = (rand() % 5 == 0) ? '*' : '.';
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (field[i][j] == '*') {
          continue;
        }
        int mineCount = countMines(field, n, m, i, j);
        field[i][j] = mineCount + '0';
      }
    }
    printField(field, n, m);
    freeField(field, n);
  }
  return 0;
}