#ifndef MATH_H

#define MATH_H
#include "../shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long double add(long double a, long double b);
long double minus(long double a, long double b);
long double divide(long double a, long double b);
long double krat(long double a, long double b);
char (*build(char buff[MAX_INPUT_LEN]))[MAX_INPUT_LEN];
long double eval(char buff[MAX_INPUT_LEN][MAX_INPUT_LEN]);
long double math(char buff[MAX_INPUT_LEN]);
#endif
