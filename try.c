//
// Created by hakakian on 12/11/24.
//
#include <stdio.h>
#include <stdarg.h>

// self implementation of printF

//%d
int void_printfDecimal(int num) {
    if (num == 0) {
      putchar('0');
      return 0;
    }
    if (num < 0) {
      putchar('-');
      num = -num;
    }
    else{
      int index = 0;
      char array[11];  // 11 because  maximum value for a signed 32-bit integer is:2^31 -1 = 2147483647 + one space for null character \0
      while (index > 0) {
        putchar(array[--index]);
      }

    }










