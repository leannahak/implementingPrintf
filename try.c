//
// Created by hakakian on 12/11/24.
//
#include <stdio.h>
#include <stdarg.h>

// int --> str
void intToString(int value, char *buffer) {
  int i = 0 ;
  int isNegative = 0 ;

  if (value < 0) {
    isNegative = 1;
    value = -value;
    }

    do {
      buffer[i++] = value % 10 + '0' ;
      value /= 10
     } while (value > 0);

     if (isNegative)












