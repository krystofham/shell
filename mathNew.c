#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
long double add(long double a, long double b) { return a + b; }
long double minus(long double a, long double b) { return a - b; }
long double divide(long double a, long double b) { return a / b; }
long double krat(long double a, long double b) { return a * b; }
// Build buffer
int build(char buff[MAX_INPUT_LEN]) {
  char *p = malloc(sizeof(char) * MAX_INPUT_LEN * MAX_INPUT_LEN * 2);
  long int active_index = 0;
  long int start_index, end_index;
  int active_num = 0;
  for (int a = 0; a < MAX_INPUT_LEN * MAX_INPUT_LEN; a++) {
    if (buff[a] == '/' || buff[a] == '*' || buff[a] == '-' || buff[a] == '+' ||
        buff[a] == '(' || buff[a] == ')') {
      if (active_num) {
        active_num = 0;
        end_index = a - 1;
      }
      p[active_index][0] = b[a];
      active_index++;
    } else {
      if (!active_num) {

        // stale Num
        // Num
        active_num = 1;
      }
    }
  }
  return p;
}
long double eval(char buff[MAX_INPUT_LEN][MAX_INPUT_LEN]) {
  // Zavorky
  int zavorka_count = 0;
  for (int a = 0; a < MAX_INPUT_LEN; a++) {
    if (buff[a] == "(") {
      zavorka_count++;
    }
  }
  int start_index, end_index;
  while (zavorka_count != 0) {
    for (int a = 0; a < MAX_INPUT_LEN; a++) {

      if (buff[a] == '(') {
        start_index = a;
      } else if (buff[a] == ')') {
        end_index = a;
        char bu[MAX_INPUT_LEN][MAX_INPUT_LEN];
        // Doplnit ze stareho
        long double vysledek = eval(bu);
        // Dopsat do buffu vysledek
        zavorka_count--;
      }
    }
  }
  // Nasobeni
  zavorka_count = 0;
  for (int a = 0; a < MAX_INPUT_LEN; a++) {
    if (buff[a] == '*' || buff[a] == '-') {
      zavorka_count++;
    }
  }
  while (zavorka_count != 0) {
    for (int a = 0; a < MAX_INPUT_LEN; a++) {
      if (buff[a] == '*') {
        long double vysledek = krat(strtold(buff[a - 1]), strtold(buff[a + 1]));
        // Zapsat do buffu
      } else if (buff[a] == '/') {
        long double vysledek =
            divide(strtold(buff[a - 1]), strtold(buff[a + 1]));
        // Zapsat do buffu
      }
    }
  }
}
