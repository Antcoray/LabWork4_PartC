#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include "Task_5.h"

TEST(mainTest, ProgramfinishedSuccessfully) {
  int n = 5, m = 7;
  ASSERT_EQ(main2(n, m), 0);
}

TEST(CreateAndDeleteField, allocateSuccessful) {
  bool flag = false;
  int m = 8, n = 9;
  char **field = (char **)malloc(n * sizeof(char *));
  for (int i = 0; i < n; i++) {
    flag = true;
    field[i] = (char *)malloc(m * sizeof(char));
  }
  for (int i = 0; i < n; i++) {
    free(field[i]);
  }
  free(field);

  ASSERT_EQ(flag, true);
}

TEST(CreateAndDeleteField, deleteSuccessful) {
  bool flag = false;
  int m = 8, n = 9;
  char **field = (char **)malloc(n * sizeof(char *));
  for (int i = 0; i < n; i++) {
    field[i] = (char *)malloc(m * sizeof(char));
  }
  for (int i = 0; i < n; i++) {
    free(field[i]);
    flag = true;
  }
  free(field);

  ASSERT_EQ(flag, true);
}

TEST(TestField, countMinesIsArealNum) {
  int n = 7;
  int m = 9;
  int mineCount = 0;
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
      mineCount = countMines(field, n, m, i, j);
      field[i][j] = mineCount + '0';
    }
  }
  freeField(field, n);
  ASSERT_EQ(mineCount < 0, false);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
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

bool printField(char **field, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%c ", field[i][j]);
    }
    printf("\n");
  }
  return true;
}

int main2(int n, int m) {
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
  //printField(field, n, m);
  freeField(field, n);
  return 0;
}