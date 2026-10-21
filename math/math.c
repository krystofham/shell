#include "math.h"
#include <stdio.h>
long double hoursSpendOnThis = 10.5; // Should invent long long double due to
                                     // this
long double add(long double a, long double b) { return a + b; }
long double minus(long double a, long double b) { return a - b; }
long double divide(long double a, long double b) { return a / b; }
long double krat(long double a, long double b) { return a * b; }
// Build buffer
// CHybí testy pro build
long double math(char buff[MAX_INPUT_LEN]) {
  char (*p)[MAX_INPUT_LEN] = build(buff);
  long double vysledek = eval(p);
  free(p);
  printf("%Lf\n", vysledek);
  return vysledek;
}
char (*build(char buff[MAX_INPUT_LEN])) [MAX_INPUT_LEN] {
  char (*p)[MAX_INPUT_LEN] = calloc(MAX_INPUT_LEN, sizeof *p);
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
}
// SEM TO NEJAK FUNGUJE, NESAHAT

long double eval(char buff[MAX_INPUT_LEN][MAX_INPUT_LEN]) {
  // Zavorky
  int zavorka_count = 0;
  printf("Zavorky \n");
  for (int i = 0; i < 10; i++) {
    printf("%d - %s\n", i, buff[i]);
  }
  for (int a = 0; a < MAX_INPUT_LEN; a++) {
    for (int b = 0; b < MAX_INPUT_LEN; b++) {
      if (buff[a][b] == '(') {
        zavorka_count++;
      } else if (buff[a][b] == '\0') {
        break;
      }
    }
  }
  // Jdeme po závorkách a rekurzivně zmenšuju výraz
  int start_index = 0, end_index;
  while (zavorka_count != 0) {
    printf("Zavorky ON \n");
    for (int a = 0; a < MAX_INPUT_LEN; a++) {
      for (int b = 0; b < MAX_INPUT_LEN; b++) {
        if (buff[a][b] == '\0') {
          break;
        }
        if (strcmp(buff[a], "(") == 0) {
          start_index = a;
        } else if (strcmp(buff[a], ")") == 0) {
          // Máme výraz v závorce (jeho indexy), toto zkopírujeme do bu a tento
          // zjednodušený výraz bez závorek rekurzivně dáváme dále
          end_index = a;
          char bu[MAX_INPUT_LEN][MAX_INPUT_LEN] = {0};
          // Doplnit ze stareho
          int j = 0;
          for (int i = start_index + 1; i < end_index; i++) {
            if (buff[i][0] == '\0') {
              break;
            }
            strcpy(bu[j], buff[i]);
            j++;
          }
          for (int i = 0; i < 10; i++) {
            printf("%d - %s\n", i, bu[i]);
          }
          long double vysledek = eval(bu);
          // Dopsat do buffu vysledek
          char new_buff_after_vysledek[MAX_INPUT_LEN][MAX_INPUT_LEN] = {0};
          int index = 0;
          // Zapiseme novy buffer do ktereho vblozime misto zavorek vysledek
          for (int i = 0; i < MAX_INPUT_LEN; i++) {
            if (i != 0) {
              printf("%s", new_buff_after_vysledek[i - 1]);
            }
            if (i < start_index) {
              strcpy(new_buff_after_vysledek[index], buff[i]);
            } else if (i == start_index) {
              // start index
              sprintf(new_buff_after_vysledek[index], "%Lf", vysledek);
              i = end_index;
            } else {
              // za end
              strcpy(new_buff_after_vysledek[index], buff[i]);
            }
            index++;
          }
          // Prepiseme buffer aby to fungovalo dale
          for (int i = 0; i < MAX_INPUT_LEN; i++) {
            strcpy(buff[i], new_buff_after_vysledek[i]);
          }
          zavorka_count--;
          b = 0;
          a = 0;
        }
      }
    }
  }
  // TADY TO MOZNA TROCHU FACHA POD TIM JE TO COOKED - pod tim delane v hdoine
  // Nasobeni
  zavorka_count = 0;
  for (int a = 0; a < MAX_INPUT_LEN; a++) {
    if (strcmp(buff[a], "*") == 0 || strcmp(buff[a], "/") == 0) {
      zavorka_count++;
    }
  }
  while (zavorka_count != 0) {
    printf("Nasobeni ON \n");
    for (int a = 0; a < MAX_INPUT_LEN - 2; a++) {
      if (strcmp(buff[a], "*") == 0) {
        long double vysledek =
            krat(strtold(buff[a - 1], NULL), strtold(buff[a + 1], NULL));
        // Zapsat do buffu
        char new_buff_after_vysledek[MAX_INPUT_LEN][MAX_INPUT_LEN] = {0};
        for (int i = 0; i < MAX_INPUT_LEN - 2; i++) {
          if (i < (a - 1)) {
            strcpy(new_buff_after_vysledek[i], buff[i]);
          } else if (i == (a - 1)) {
            sprintf(new_buff_after_vysledek[i], "%Lf", vysledek);
          } else {
            strcpy(new_buff_after_vysledek[i],
                   buff[i + 2]); // +2 protoze vysledek operace ma 3 mista v
                                 // bufferu
          }
        }
        for (int i = 0; i < MAX_INPUT_LEN - 2; i++) {
          strcpy(buff[i], new_buff_after_vysledek[i]);
        }
        zavorka_count--;
        a = 0;
      } else if (strcmp(buff[a], "/") == 0) {
        long double vysledek =
            divide(strtold(buff[a - 1], NULL), strtold(buff[a + 1], NULL));
        // Zapsat do buffu
        char new_buff_after_vysledek[MAX_INPUT_LEN][MAX_INPUT_LEN] = {0};
        for (int i = 0; i < MAX_INPUT_LEN - 2; i++) {
          if (i < (a - 1)) {
            strcpy(new_buff_after_vysledek[i], buff[i]);
          } else if (i == (a - 1)) {
            sprintf(new_buff_after_vysledek[i], "%Lf", vysledek);
          } else {
            strcpy(new_buff_after_vysledek[i],
                   buff[i + 2]); // +2 protoze vysledek operace ma 3 mista v
                                 // bufferu
          }
        }
        for (int i = 0; i < MAX_INPUT_LEN; i++) {
          strcpy(buff[i], new_buff_after_vysledek[i]);
        }
        zavorka_count--;
        a = 0;
      }
    }
  }
  // Scitani
  zavorka_count = 0;
  for (int a = 0; a < MAX_INPUT_LEN; a++) {
    if (strcmp(buff[a], "+") == 0 || strcmp(buff[a], "-") == 0) {
      zavorka_count++;
    }
  }
  while (zavorka_count != 0) {
    for (int a = 0; a < MAX_INPUT_LEN; a++) {
      if (strcmp(buff[a], "+") == 0) {
        long double vysledek =
            add(strtold(buff[a - 1], NULL), strtold(buff[a + 1], NULL));
        // Zapsat do buffu
        char new_buff_after_vysledek[MAX_INPUT_LEN][MAX_INPUT_LEN] = {0};
        for (int i = 0; i < MAX_INPUT_LEN - 2; i++) {
          if (i < (a - 1)) {
            strcpy(new_buff_after_vysledek[i], buff[i]);
          } else if (i == (a - 1)) {
            sprintf(new_buff_after_vysledek[i], "%Lf", vysledek);
          } else {
            strcpy(new_buff_after_vysledek[i],
                   buff[i + 2]); // +2 protoze vysledek operace ma 3 mista v
                                 // bufferu
          }
        }
        for (int i = 0; i < MAX_INPUT_LEN; i++) {
          strcpy(buff[i], new_buff_after_vysledek[i]);
        }
        zavorka_count--;
        a = 0;
      } else if (strcmp(buff[a], "-") == 0) {
        long double vysledek =
            minus(strtold(buff[a - 1], NULL), strtold(buff[a + 1], NULL));
        // Zapsat do buffu
        char new_buff_after_vysledek[MAX_INPUT_LEN][MAX_INPUT_LEN] = {0};
        for (int i = 0; i < MAX_INPUT_LEN - 2; i++) {
          if (i < (a - 1)) {
            strcpy(new_buff_after_vysledek[i], buff[i]);
          } else if (i == (a - 1)) {
            sprintf(new_buff_after_vysledek[i], "%Lf", vysledek);
          } else {
            strcpy(new_buff_after_vysledek[i],
                   buff[i + 2]); // +2 protoze vysledek operace ma 3 mista v
                                 // bufferu
          }
        }
        for (int i = 0; i < MAX_INPUT_LEN; i++) {
          strcpy(buff[i], new_buff_after_vysledek[i]);
        }
        zavorka_count--;
        a = 0;
      }
    }
  }
  return strtold(buff[0], NULL);
}

// Chybí část pro doplnění typu 2(2+3)
// CHybí funkce pro dosazení do rovnice 2(3+5) -> 4x+6/8 // napsat v rustu??
// Chybí minus -3+5(-5+9) - asi udelat tak ze pred to dam 0
// Chybí ^ nebo zapis **
