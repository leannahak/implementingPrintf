#include <stdarg.h>
#include <string.h>
#include <stdio.h>

// Error codes
#define SUCCESS 0
#define NULL_POINTER_ERROR 1
#define BUFFER_SIZE_ERROR 2

// int --> str
int intToString(int value, char *buffer, size_t bufferSize) {
    if (!buffer || bufferSize < 2) return NULL_POINTER_ERROR;

    int i = 0;
    int isNegative = 0;

    if (value < 0) {
        isNegative = 1;
        value = -value;
    }

    do {
        if (i >= bufferSize - 1) return BUFFER_SIZE_ERROR; // Prevent overflow
        buffer[i++] = value % 10 + '0';
        value /= 10;
    } while (value > 0);

    if (isNegative) {
        if (i >= bufferSize - 1) return BUFFER_SIZE_ERROR; // Prevent overflow
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = temp;
    }

    return SUCCESS;
}

// int --> hex
int intToHex(unsigned int value, char *buffer, size_t bufferSize) {
    if (!buffer || bufferSize < 2) return NULL_POINTER_ERROR;

    const char *hexChars = "0123456789abcdef";
    int i = 0;

    do {
        if (i >= bufferSize - 1) return BUFFER_SIZE_ERROR; // Prevent overflow
        buffer[i++] = hexChars[value % 16];
        value /= 16;
    } while (value > 0);

    buffer[i] = '\0';

    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = temp;
    }

    return SUCCESS;
}

// reverse an inputted string
int reverseString(char *str) {
    if (!str) return NULL_POINTER_ERROR;

    int len = 0;
    while (str[len]) len++;

    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }

    return SUCCESS;
}

// convert inputted string to uppercase
int stringToUpper(char *str) {
    if (!str) return NULL_POINTER_ERROR;

    while (*str) {
        if (*str >= 'a' && *str <= 'z') {
            *str -= ('a' - 'A');
        }
        str++;
    }

    return SUCCESS;
}

// int --> binary
int intToBinary(unsigned int value, char *buffer, size_t bufferSize) {
    if (!buffer || bufferSize < 2) return NULL_POINTER_ERROR;

    int i = 0;

    do {
        if (i >= bufferSize - 1) return BUFFER_SIZE_ERROR; // Prevent overflow
        buffer[i++] = (value % 2) + '0';
        value /= 2;
    } while (value > 0);

    buffer[i] = '\0';

    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = temp;
    }

    return SUCCESS;
}

// custom printf implementation using putchar
int my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;

            int width = 0;
            while (*format >= '0' && *format <= '9') {
                width = width * 10 + (*format - '0');
                format++;
            }

            char buffer[128];
            int result = SUCCESS;

            switch (*format) {
                case 'd': {
                    int value = va_arg(args, int);
                    result = intToString(value, buffer, sizeof(buffer));
                    if (result == SUCCESS) {
                        int len = strlen(buffer);
                        for (int i = 0; i < width - len; i++) putchar(' ');
                        for (char *p = buffer; *p; p++) putchar(*p);
                    }
                    break;
                }
                case 'x': {
                    unsigned int value = va_arg(args, unsigned int);
                    result = intToHex(value, buffer, sizeof(buffer));
                    if (result == SUCCESS) {
                        int len = strlen(buffer);
                        for (int i = 0; i < width - len; i++) putchar(' ');
                        for (char *p = buffer; *p; p++) putchar(*p);
                    }
                    break;
                }
                case 'b': {
                    unsigned int value = va_arg(args, unsigned int);
                    result = intToBinary(value, buffer, sizeof(buffer));
                    if (result == SUCCESS) {
                        for (char *p = buffer; *p; p++) putchar(*p);
                    }
                    break;
                }
                case 'r': {
                    char *str = va_arg(args, char *);
                    if (str == NULL) str = "(null)";
                    strncpy(buffer, str, sizeof(buffer) - 1);
                    buffer[sizeof(buffer) - 1] = '\0';
                    result = reverseString(buffer);
                    if (result == SUCCESS) {
                        for (char *p = buffer; *p; p++) putchar(*p);
                    }
                    break;
                }
                case 'u': {
                    char *str = va_arg(args, char *);
                    if (str == NULL) str = "(null)";
                    strncpy(buffer, str, sizeof(buffer) - 1);
                    buffer[sizeof(buffer) - 1] = '\0';
                    result = stringToUpper(buffer);
                    if (result == SUCCESS) {
                        for (char *p = buffer; *p; p++) putchar(*p);
                    }
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    putchar(c);
                    break;
                }
                case 's': {
                    char *str = va_arg(args, char *);
                    if (str == NULL) str = "(null)";
                    strncpy(buffer, str, sizeof(buffer) - 1);
                    buffer[sizeof(buffer) - 1] = '\0';
                    for (char *p = buffer; *p; p++) putchar(*p);
                    break;
                }
                default:
                    putchar('%');
                    putchar(*format);
                    break;
            }
        } else {
            putchar(*format);
        }
        format++;
    }

    va_end(args);
    return SUCCESS;
}

// Main function with tests
int main() {
    my_printf("===== Testing my_printf =====\n");

    // Integer Conversion Tests
    my_printf("Test Integer Positive: Expected: '  123', Output: '%5d'\n", 123);
    my_printf("Test Integer Negative: Expected: ' -123', Output: '%5d'\n", -123);
    my_printf("Test Integer Zero: Expected: '    0', Output: '%5d'\n", 0);
    my_printf("Test Integer No Width: Expected: '456', Output: '%d'\n", 456);

    // Hexadecimal Conversion Tests
    my_printf("Test Hex Positive: Expected: '      ff', Output: '%08x'\n", 255);
    my_printf("Test Hex Large: Expected: '   ffff', Output: '%8x'\n", 65535);
    my_printf("Test Hex Zero: Expected: '0', Output: '%x'\n", 0);

    // Binary Conversion Tests
    my_printf("Test Binary Small: Expected: '111', Output: '%b'\n", 7);
    my_printf("Test Binary Large: Expected: '1111111111', Output: '%b'\n", 1023);
    my_printf("Test Binary Zero: Expected: '0', Output: '%b'\n", 0);

    // Reverse String Tests
    my_printf("Test Reverse Normal: Expected: 'olleH', Output: '%r'\n", "Hello");
    my_printf("Test Reverse Empty: Expected: '', Output: '%r'\n", "");
    my_printf("Test Reverse Null: Expected: '(null)', Output: '%r'\n", NULL);

    // Uppercase String Tests
    my_printf("Test Uppercase Normal: Expected: 'WORLD', Output: '%u'\n", "world");
    my_printf("Test Uppercase Mixed: Expected: 'HELLO123', Output: '%u'\n", "hElLo123");
    my_printf("Test Uppercase Empty: Expected: '', Output: '%u'\n", "");
    my_printf("Test Uppercase Null: Expected: '(null)', Output: '%u'\n", NULL);

    // Character Tests
    my_printf("Test Character Simple: Expected: 'A', Output: '%c'\n", 'A');
    my_printf("Test Character Padded: Expected: '    B', Output: '%5c'\n", 'B');
    my_printf("Test Character Zero Width: Expected: 'Z', Output: '%c'\n", 'Z');

    // String Tests
    my_printf("Test String Normal: Expected: '       Hi!', Output: '%10s'\n", "Hi!");
    my_printf("Test String Short: Expected: 'Hi!', Output: '%2s'\n", "Hi!");
    my_printf("Test String Exact Width: Expected: 'Hey', Output: '%3s'\n", "Hey");
    my_printf("Test String Null: Expected: '(null)', Output: '%8s'\n", NULL);
    my_printf("Test String Empty: Expected: '', Output: '%5s'\n", "");

    // Mixed Formatting Tests
    my_printf("Test Mixed Formatting: Expected: '   42 |      ff |     X |    Mixed!', Output: '%5d | %8x | %5c | %10s'\n", 42, 255, 'X', "Mixed!");

    // Edge Case Tests
    my_printf("Test Large Decimal: Expected: '2147483647', Output: '%d'\n", 2147483647); // INT_MAX
    my_printf("Test Small Decimal: Expected: '-2147483648', Output: '%d'\n", -2147483648); // INT_MIN
    my_printf("Test Large Hexadecimal: Expected: 'ffffffff', Output: '%x'\n", 4294967295U); // UINT_MAX
    my_printf("Test Large Binary: Expected: '1111111111111111', Output: '%b'\n", 65535);

    my_printf("===== Tests Completed =====\n");

    return 0;
}