#include "math.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int MAX_INPUT_LEN = 1024;
int main(int argc, char *argv[]) {
  while (1) {
    printf("> ");
    fflush(stdout);
    char input[MAX_INPUT_LEN];
    if (fgets(input, MAX_INPUT_LEN, stdin) == NULL) {
      perror("fgets failed");
      continue;
    }
    if (strcmp(input, "exit\n")) {
      return 0;
    }
    for (int a; a < MAX_INPUT_LEN; a++) {
      char i = input[a];
      // MATH OPERATIONES
      if ((i == '+' || i == '-' || i == '*' || i == '/') &&) {
        math(input);
      }
      if (i = '') {
        break;
      }
    }

    system(input);
  }
}
