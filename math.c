#include "main.h"
#include <string.h>
#define smycka for (int a = 0; a < MAX_INPUT_LEN; a++)
#define operator                                                               \
  if (i == '+' || i == '-' || i == '*' || i == '/' || i == '(' || i == ')')

long double add(long double a, long double b) { return a + b; }
long double minus(long double a, long double b) { return a - b; }
long double divide(long double a, long double b) { return a / b; }
long double krat(long double a, long double b) { return a * b; }
long long int eval(char buff[MAX_INPUT_LEN], int expression_count) {
  smycka {
    char i = buff[a];
    if (expression_count > 2) {
      operator { eval(buff, expression_count - 1); }
      else {
        buff[a] = '\0';
      }
    } else {
      operator {
        char left[MAX_INPUT_LEN];
        char right[MAX_INPUT_LEN];
        for (int b; b < MAX_INPUT_LEN; b++) {
          char o = buff[b];
          if (b > a) {
            right[b] = o;
          } else if (b < a) {
            left[b] = o;
          }
        }
        long double le = strtold(left, NULL);
        long double ri = strtold(right, NULL);
        if (i == '+') {
          return add(le, ri);
        } else if (i == '-') {
          return minus(le, ri);
        } else if (i == '*') {
          return krat(le, ri);
        } else if (i == '/') {
          return divide(le, ri);
        }
      }
    }
  }
}
int math(char input[MAX_INPUT_LEN]) {
  // DIVIDE INTO CHUNCKS
  int chuncks_count = 0;
  int breakpoints[MAX_INPUT_LEN / 2];
  smycka {
    char i = input[a];
    operator {
      breakpoints[chuncks_count] = (int)a;
      chuncks_count++;
    }
  }
  char buff[MAX_INPUT_LEN];
  char chunks[MAX_INPUT_LEN][MAX_INPUT_LEN];
  int current_breakpoint = breakpoints[0];
  int index_current_breakpoint = 0;
  int index = 0;
  smycka {
    char i = input[a];
    if (a == current_breakpoint) {
      strcpy(buff, chunks[index_current_breakpoint]);
      index_current_breakpoint++;
      current_breakpoint = breakpoints[index_current_breakpoint];
      index = 0;
    } else {
      buff[index] = i;
      index++;
    }
  }
  eval(buff, MAX_INPUT_LEN);
  return 0;
}
