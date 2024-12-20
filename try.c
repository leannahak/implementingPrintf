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
        case 'b' : {
          unsigned int value = va_args(args, unsigned int);
          char buffer[32];
          intToBinary(value, buffer);
          for (char *p = buffer; *p; p++) putchar(*p);
          break;
        }
        case 'r' : {
          char *str = va_arg(args, char *);
          if (str == NULL) str = "(null)";
          char buffer[128];
          int i = 0;
          while(str[i]) {
            buffer[i] = str[i];
            i++;
          }
          buffer[i] = '\0';
          reverseString(buffer);
          for (char*p = buffer; *p; p++) putchar(*p);
          break;
        }
        case 'u': {
          char *str = va_arg(args, char *);
          if (str == NULL) str = "(null)";
          char buffer[128];
          int i = 0;
          while (str[i]) {
            buffer[i] = str[i];
            i++;
          }
          buffer[i] = '\0';
          stringToUpper(buffer);
          for (char *p = buffer; *p; p++) putchar(*p);
          break;
        }
        case 'c': {
          char *str= va_arg(args, char *);
          char c = (char) va_arg(args, int);
          for (int i = 0; i< width-1; i++) putchar(' ');
          putchar(c);
          break;
        }
        case 's' : {
          char *str = va_arg(args, char *);
          if (str == NULL) str = "(null)";
          int len = 0
          while (str[len]) len++;
          for (int i=0; i< width-len;i++) putchar(' ');
          while (*str) putchar(*str++);
          break;
        }
        default:
          putchar('%');
        putchar(*format);
        break;
      }
    } else {
      putchar(*format); // Print regular characters
    }
    format++;
  }

  va_end(args);
  return 0; // Success
}
int main() {
  my_printf("Decimal: %5d\n", 123);
  my_printf("Hexadecimal: %8x\n", 255);
  my_printf("Binary: %b\n", 7);           // 111
  my_printf("Reverse: %r\n", "Hello");    // olleH
  my_printf("Uppercase: %u\n", "world");  // WORLD
  my_printf("Character: %3c\n", 'A');
  my_printf("String: %10s\n", "Hi!");
  my_printf("String (null): %8s\n", NULL);
  return 0;
}





















