#pragma once

char **allocateField(int n, int m);
void freeField(char **field, int n);
int countMines(char **field, int n, int m, int i, int j);
bool printField(char **field, int n, int m);
int main2(int n,int m);