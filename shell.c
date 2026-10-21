#include "shell.h"
#include "math/math.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  while (1) {
    printf("> ");
    fflush(stdout);
    char input[MAX_INPUT_LEN];
    if (fgets(input, MAX_INPUT_LEN, stdin) == NULL) {
      perror("fgets failed\n");
      continue;
    }
    if (strcmp(input, "exit\n") == 0) {
      printf("strcmp");
      return 0;
    }
    int mathOn = 0;
    for (int a = 0; a < MAX_INPUT_LEN; a++) {
      char i = input[a];
      // MATH OPERATIONES
      if (input[0] == 'm') {
        // math
        for (int b = 0; b < MAX_INPUT_LEN - 1; b++) {
          if (b == 0) {
            continue;
          } else {
            input[b - 1] = input[b];
          }
        }
        mathOn = 1;
        break;
      }
      if (i == '\0') {
        break;
      }
    }
    if (mathOn) {
      math(input);
    } else {
      system(input);
    }
  }
  return 0;
}
