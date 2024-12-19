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
      value /= 10;
     } while (value > 0);

     if (isNegative) buffer[i++] = "-";
     buffer[i] = '\0';

     for (int j =0 , k= i-1; j<k ; j++,k--) {
       char temp = buffer[j];
       buffer[j] = buffer[k];
       buffer[k] = temp;
     }
}

// int --> hex
void intToHex(unsigned int value, char *buffer){
  const char *hexChars = "0123456789abcdef";
  int i = 0;

  do {
    buffer[i++] = hexChars[value % 16];
    value /= 16;
  } while (value > 0);

  buffer[i] = '\0';

  for ( int j =0,  k = i-1; j<k; j++, k--) {
    char temp = buffer[j];
    buffer[j] = buffer[k];
    buffer[k] = temp;
  }
}

// creative function to reverse an inputted string
void reverseString(char *str) {
  int len = 0;
  while (str[len]) len++;
  for (int i =0, j= len-1; i<j ; i++,j--) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
}

//creative function to make inputted string to all uppercase
void stringToUpper(char *str) {
  while(*str){
    if (*str >= 'a' && *str <= 'z') {
      *str = *str - ('a' - 'A');
    }
    str++;
    }
}

// creative function to convert to binary
void intToBinary(unsigned int value, char *buffer) {
  int i = 0;

  do {
    buffer[i++] = (value %2 ) + '0';
    value /= 2;
  } while (value > 0);

  buffer[i] = '\0';
  for (int j = 0, k = i - 1; j < k; j++, k--) {
    char temp = buffer[j];
    buffer[j] = buffer[k];
    buffer[k] = temp;
  }
}

// my own custom printf implementation
void my_printf(const char *format, ...) {
  va_list args;
  va_start(args,format);

  while (*format) {
    if (*format == '%') {
      format++;

      int width = 0;
      while (*format >= '0' && *format <= '9'){
        width = width*10 + (*format - '0');
        format++;
      }

      switch (*format) {
        case 'd': {
          int value = va_arg(args, int);
          char buffer[32];
          intToString(value, buffer);

          int len = 0;
          while (buffer[len]) len++;
          for (int i = 0; i<width-len;i++) putchar(' ');
          for (char *p = buffer; *p;p++) putchar(*p);
          break;
        }
        case 'x': {
          unsigned int value = va_arg(args, unsigned int);
          char buffer[32];
          intToHex(value, buffer);
          int len = 0;
          while (buffer[len]) len++;
          for (int i = 0; i<width-len;i++) putchar(' ');
          for (char *p = buffer; *p;p++) putchar(*p);
          break;
        }




      }















