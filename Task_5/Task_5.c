#include <stdio.h>
#include <stdlib.h>

void printField(char **field, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%c ", field[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int n, m;
  printf("Введите размер поля n и m: ");
  scanf("%d %d", &n, &m);

  char field = (char)malloc(n * sizeof(char *));
  for (int i = 0; i < n; i++) {
    field[i] = (char *)malloc(m * sizeof(char));
    for (int j = 0; j < m; j++) {
      field[i][j] = (rand() % 5 == 0) ? '*' : '.';
    }
  }

  int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (field[i][j] == '*') continue;

      int count = 0;
      for (int d = 0; d < 8; d++) {
        int ni = i + dx[d];
        int nj = j + dy[d];
        if (ni >= 0 && ni < n && nj >= 0 && nj < m && field[ni][nj] == '*') {
          count++;
        }
      }
      field[i][j] = count + '0';
    }
  }

  printField(field, n, m);

  for (int i = 0; i < n; i++) {
    free(field[i]);
  }
  free(field);

  return 0;
}