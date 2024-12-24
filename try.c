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

     if (isNegative) buffer[i++] = '-';
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
          unsigned int value = va_arg(args, unsigned int);
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
          //char *str= va_arg(args, char *);
          char c = (char) va_arg(args, int);
          for (int i = 0; i< width-1; i++) putchar(' ');
          putchar(c);
          break;
        }
        case 's' : {
          char *str = va_arg(args, char *);
          if (str == NULL) str = "(null)";
          int len = 0;
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
  return; // Success
}
int main() {
    printf("===== Testing my_printf =====\n");

    // Integer Conversion Tests
    printf("Test Integer Positive: ");
    my_printf("Expected: '  123', Output: '%5d'\n", 123);

    printf("Test Integer Negative: ");
    my_printf("Expected: ' -123', Output: '%5d'\n", -123);

    printf("Test Integer Zero: ");
    my_printf("Expected: '    0', Output: '%5d'\n", 0);

    printf("Test Integer No Width: ");
    my_printf("Expected: '456', Output: '%d'\n", 456);

    // Hexadecimal Conversion Tests
    printf("Test Hex Positive: ");
    my_printf("Expected: '000000ff', Output: '%08x'\n", 255);

    printf("Test Hex Large: ");
    my_printf("Expected: '   ffff', Output: '%8x'\n", 65535);

    printf("Test Hex Zero: ");
    my_printf("Expected: '0', Output: '%x'\n", 0);

    // Binary Conversion Tests
    printf("Test Binary Small: ");
    my_printf("Expected: '111', Output: '%b'\n", 7);

    printf("Test Binary Large: ");
    my_printf("Expected: '1111111111', Output: '%b'\n", 1023);

    printf("Test Binary Zero: ");
    my_printf("Expected: '0', Output: '%b'\n", 0);

    // Reverse String Tests
    printf("Test Reverse Normal: ");
    my_printf("Expected: 'olleH', Output: '%r'\n", "Hello");

    printf("Test Reverse Empty: ");
    my_printf("Expected: '', Output: '%r'\n", "");

    printf("Test Reverse Null: ");
    my_printf("Expected: '(null)', Output: '%r'\n", NULL);

    // Uppercase String Tests
    printf("Test Uppercase Normal: ");
    my_printf("Expected: 'WORLD', Output: '%u'\n", "world");

    printf("Test Uppercase Mixed: ");
    my_printf("Expected: 'HELLO123', Output: '%u'\n", "hElLo123");

    printf("Test Uppercase Empty: ");
    my_printf("Expected: '', Output: '%u'\n", "");

    printf("Test Uppercase Null: ");
    my_printf("Expected: '(null)', Output: '%u'\n", NULL);

    // Character Tests
    printf("Test Character Simple: ");
    my_printf("Expected: 'A', Output: '%c'\n", 'A');

    printf("Test Character Padded: ");
    my_printf("Expected: '    B', Output: '%5c'\n", 'B');

    printf("Test Character Zero Width: ");
    my_printf("Expected: 'Z', Output: '%c'\n", 'Z');

    // String Tests
    printf("Test String Normal: ");
    my_printf("Expected: '       Hi!', Output: '%10s'\n", "Hi!");

    printf("Test String Short: ");
    my_printf("Expected: 'Hi!', Output: '%2s'\n", "Hi!");

    printf("Test String Exact Width: ");
    my_printf("Expected: 'Hey', Output: '%3s'\n", "Hey");

    printf("Test String Null: ");
    my_printf("Expected: '(null)', Output: '%8s'\n", NULL);

    printf("Test String Empty: ");
    my_printf("Expected: '', Output: '%5s'\n", "");

    // Mixed Formatting Tests
    printf("Test Mixed Formatting: ");
    my_printf("Expected: '   42 |      ff |     X |    Mixed!', Output: '%5d | %8x | %5c | %10s'\n", 42, 255, 'X', "Mixed!");

    // Edge Case Tests
    printf("Test Large Decimal: ");
    my_printf("Expected: '2147483647', Output: '%d'\n", 2147483647); // INT_MAX

    printf("Test Small Decimal: ");
    my_printf("Expected: '-2147483648', Output: '%d'\n", -2147483648); // INT_MIN

    printf("Test Large Hexadecimal: ");
    my_printf("Expected: 'ffffffff', Output: '%x'\n", 4294967295U); // UINT_MAX

    printf("Test Large Binary: ");
    my_printf("Expected: '1111111111111111', Output: '%b'\n", 65535);

    printf("===== Tests Completed =====\n");

    return 0;
}























