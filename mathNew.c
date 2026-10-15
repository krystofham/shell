#include "shell.h"
#include <stdlib.h>
#include <string.h>
long double hoursSpendOnThis = 6.0; // Should invent long long double due to
                                    // this
long double add(long double a, long double b) { return a + b; }
long double minus(long double a, long double b) { return a - b; }
long double divide(long double a, long double b) { return a / b; }
long double krat(long double a, long double b) { return a * b; }
// Build buffer
// CHybí testy pro build
char (*build(char buff[MAX_INPUT_LEN])) [MAX_INPUT_LEN] {
  char (*p)[MAX_INPUT_LEN] = malloc(MAX_INPUT_LEN * sizeof *p);
  long int active_index = 0;
  long int start_index, end_index;
  int active_num = 0;
  for (int a = 0; a < MAX_INPUT_LEN; a++) {
    if (buff[a] == '/' || buff[a] == '*' || buff[a] == '-' || buff[a] == '+' ||
        buff[a] == '(' || buff[a] == ')' || buff[a] == '\0') {
      if (active_num) {
        active_num = 0;
        end_index = a - 1;
        // p[active_index] má v sobě list od buff[sart_index] po buff[end_index]
        // strncpy(cil, zdroj + od_indexu, delka);
        strncpy(p[active_index], buff + start_index,
                end_index - start_index + 1);
        active_index++;
      }
      strncpy(p[active_index], buff + a, 1); // operand zabírá jedno misto
      active_index++;
    } else {
      if (!active_num) {
        // Num
        active_num = 1;
        start_index = a;
      }
    }
  }
  return p;
} long double eval(char buff[MAX_INPUT_LEN][MAX_INPUT_LEN]) {
  // Zavorky
  int zavorka_count = 0;
  for (int a = 0; a < MAX_INPUT_LEN; a++) {
    if (buff[a] == "(") {
      zavorka_count++;
    }
  }
  // Jdeme po závorkách a rekurzivně zmenšuju výraz
  int start_index, end_index;
  while (zavorka_count != 0) {
    for (int a = 0; a < MAX_INPUT_LEN; a++) {

      if (buff[a] == '(') {
        start_index = a;
      } else if (buff[a] == ')') {
        // Máme výraz v závorce (jeho indexy), toto zkopírujeme do bu a tento
        // zjednodušený výraz bez závorek rekurzivně dáváme dále
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
    if (buff[a] == '*' || buff[a] == '/') {
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
  // Scitani
  zavorka_count = 0;
  for (int a = 0; a < MAX_INPUT_LEN; a++) {
    if (buff[a] == '+' || buff[a] == '-') {
      zavorka_count++;
    }
  }
  while (zavorka_count != 0) {
    for (int a = 0; a < MAX_INPUT_LEN; a++) {
      if (buff[a] == '+') {
        long double vysledek = plus(strtold(buff[a - 1]), strtold(buff[a + 1]));
        // Zapsat do buffu
      } else if (buff[a] == '-') {
        long double vysledek =
            minus(strtold(buff[a - 1]), strtold(buff[a + 1]));
        // Zapsat do buffu
      }
    }
  }
}
