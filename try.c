// used libraries
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


// Error codes
#define success 0
#define nullPointerError 1
#define bufferSizeError 2

// defining limits for testing
#define INT_MIN (-2147483648)
#define INT_MAX (2147483647)

// int --> str conversion
int intToString(int value, char *buffer, size_t bufferSize) {
    // make sure buffer exists and there is enough room
    if (!buffer || bufferSize < 2) return bufferSizeError;

    int i = 0; //index
    int isNegative = 0; // flag for neg #s

    //special case
    if (value == INT_MIN) {
        if (bufferSize < 12) return bufferSizeError; //int_min needs at least 12 chars
        const char *minValue = "-2147483648"; //in_min in str form
        while (*minValue && i < bufferSize - 1) {
            buffer[i++] = *minValue++; //copy it into the buffer
        }
        buffer[i] = '\0';
        return success;
    }
    // if value is (-), convert to (+)
    if (value < 0) {
        isNegative = 1; // mark as (-)
        value = -value;
    }
    // convert # to str rep in rev order
    do {
        if (i >= bufferSize - 1) return bufferSizeError; // this handles overflow case
        buffer[i++] = value % 10 + '0'; // get last digit and make it a char
        value /= 10; // remove last digit
    } while (value > 0);

    // if the # is (-) add the sign
    if (isNegative) {
        if (i >= bufferSize - 1) return bufferSizeError;
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // null terminate

    // now reverses the str to get back to correct order
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = temp;
    }

    return success;
}

// unsigned int --> hex str conversion
int intToHex(unsigned int value, char *buffer, size_t bufferSize) {
    if (!buffer || bufferSize < 2) return bufferSizeError; // make sure buffer exsists and there is enough room

    const char *hexChars = "0123456789abcdef"; // hex chars
    int i = 0; // index for buffer

    // converts # to hex rep in reverse order
    do {
        if (i >= bufferSize - 1) return bufferSizeError; // prevents overflow
        buffer[i++] = hexChars[value % 16]; // get last hex digit
        value /= 16; //remove last digit
    } while (value > 0);

    buffer[i] = '\0'; // null terminate

    // now reverses the str to get back to correct order
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = temp;
    }

    return success;
}

// creative function to reverse an inputted string
int reverseString(char *str) {
    if (!str) return nullPointerError; // make sure str exists

    int len = 0;
    while (str[len]) len++; // length of the str

    // swap chars from front and back of the str
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }

    return success;
}

// creative function to convert inputted string to uppercase
int stringToUpper(char *str) {
    if (!str) return nullPointerError; // make sure str exists

    // go through the string and convert each lowercase letter to uppercase
    while (*str) {
        if (*str >= 'a' && *str <= 'z') {
            *str -= ('a' - 'A');
        }
        str++;
    }

    return success;
}

// creative function to convert unsigned int --> binary string
int intToBinary(unsigned int value, char *buffer, size_t bufferSize) {

    // make sure buffer exists and there is enough room
    if (!buffer || bufferSize < 2) return bufferSizeError;

    int i = 0; //index

    // convert each # to binary in rev order
    do {
        if (i >= bufferSize - 1) return bufferSizeError; // prevent overflow
        buffer[i++] = (value % 2) + '0'; // get last binary digit
        value /= 2; // remove it
    } while (value > 0);

    buffer[i] = '\0'; // null terminate

    // reverse string to get right order
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = temp;
    }

    return success;
}

// custom printf implementation using putchar
int my_printf(const char *format, ...) {
    if (!format) return -1; // Handle null format string

    va_list args;     // variable argument list
    va_start(args, format); // initialize that list

    int totalPrinted = 0; // Counter for the total characters printed, to ensure we handle errors like printf

    while (*format) {
        if (*format == '%') { // format specifier handling
            format++;

            int width = 0; // field width for formatting
            while (*format >= '0' && *format <= '9') {
                width = width * 10 + (*format - '0'); // parse the width
                format++;
            }

            char buffer[128]; // buffer to hold output
            int result = success; // status for helper funcs

            switch (*format) {
                case 'd': {
                    int value = va_arg(args, int); // int argument
                    result = intToString(value, buffer, sizeof(buffer)); //convert to str
                    if (result != success) return -1; // Handle errors in intToString
                    int len = strlen(buffer);
                    for (int i = 0; i < width - len; i++) { putchar(' '); totalPrinted++; }
                    for (char *p = buffer; *p; p++) { putchar(*p); totalPrinted++; }
                    break;
                }
                case 'x': {
                    unsigned int value = va_arg(args, unsigned int); //unsigned int argument
                    result = intToHex(value, buffer, sizeof(buffer)); //convert to hex
                    if (result != success) return -1; // Handle errors in intToHex
                    int len = strlen(buffer);
                    for (int i = 0; i < width - len; i++) { putchar(' '); totalPrinted++; }
                    for (char *p = buffer; *p; p++) { putchar(*p); totalPrinted++; }
                    break;
                }
                case 'b': {
                    unsigned int value = va_arg(args, unsigned int); //unsigned int argument
                    result = intToBinary(value, buffer, sizeof(buffer)); //convert to binary
                    if (result != success) return -1; // Handle errors in intToBinary
                    for (char *p = buffer; *p; p++) { putchar(*p); totalPrinted++; }
                    break;
                }
                case 'r': {
                    char *str = va_arg(args, char *); // get str argument
                    if (!str) str = "(null)"; //null string case
                    strncpy(buffer, str, sizeof(buffer) - 1); //write it to buffer
                    buffer[sizeof(buffer) - 1] = '\0'; // null terminate
                    result = reverseString(buffer); //reverse the str
                    if (result != success) return -1; // Handle errors in reverseString
                    for (char *p = buffer; *p; p++) { putchar(*p); totalPrinted++; }
                    break;
                }
                case 'u': {
                    char *str = va_arg(args, char *); // Get str argument
                    if (str == NULL) { // Handle null string
                        str = "(null)";
                        for (const char *p = str; *p; p++) putchar(*p);
                    }
                    else {
                        strncpy(buffer, str, sizeof(buffer) - 1);
                        buffer[sizeof(buffer) - 1] = '\0';
                        result = stringToUpper(buffer); //convert to upper
                        if (result != success) return -1; // handle errors
                        if (result == success) {
                            for (char *p = buffer; *p; p++) putchar(*p);
                        }

                    }
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int); //get the char argument

                    // handles output formatting for when width is specified
                    for (int i = 0; i < width - 1; i++) { putchar(' '); totalPrinted++; }
                    putchar(c); totalPrinted++;
                    break;
                }
                case 's': {
                    char *str = va_arg(args, char *); //get str argument
                    if (!str) str = "(null)"; //null str handling
                    int len = strlen(str); // str length
                    for (int i = 0; i < width - len; i++) { putchar(' '); totalPrinted++; }
                    for (char *p = str; *p; p++) { putchar(*p); totalPrinted++; }
                    break;
                }
                default: // handling the format specifiers not supported in this implementation
                    putchar('%'); totalPrinted++;
                    putchar(*format); totalPrinted++;
                    break;
            }
        } else { // jsut print the characters regularly
            putchar(*format); totalPrinted++;
        }
        format++;
    }

    va_end(args);
    return totalPrinted; // return total # chars printed
}
// Main function with tests
int main() {
    my_printf("===== Testing my_printf =====\n");

    // Integer Conversion Tests
    my_printf("Test Integer Positive: Expected: '  123', Output: '%5d'\n", 123);
    my_printf("Test Integer Negative: Expected: ' -123', Output: '%5d'\n", -123);
    my_printf("Test Integer Zero: Expected: '    0', Output: '%5d'\n", 0);
    my_printf("Test Integer No Width: Expected: '456', Output: '%d'\n", 456);
    my_printf("Test Integer Zero Padding: Expected: '   42', Output: '%05d'\n", 42);
    my_printf("Test Integer Large Positive: Expected: '2147483647', Output: '%d'\n", INT_MAX); // Largest positive integer
    my_printf("Test Integer Small Negative: Expected: '-2147483648', Output: '%d'\n", INT_MIN); // Smallest negative integer
    my_printf("=====================================================================================================\n");


    // Hexadecimal Conversion Tests
    my_printf("Test Hex Positive: Expected: '      ff', Output: '%08x'\n", 255);
    my_printf("Test Hex Large: Expected: '   ffff', Output: '%8x'\n", 65535);
    my_printf("Test Hex Zero: Expected: '0', Output: '%x'\n", 0);
    my_printf("Test Hex No Padding: Expected: 'ff', Output: '%x'\n", 255);
    my_printf("=====================================================================================================\n");



    // Binary Conversion Tests
    my_printf("Test Binary Small: Expected: '111', Output: '%b'\n", 7);
    my_printf("Test Binary Large: Expected: '1111111111', Output: '%b'\n", 1023);
    my_printf("Test Binary Edge case - Zero: Expected: '0', Output: '%b'\n", 0);
    my_printf("Test Binary  Extra Large Value: Expected: '1111111111111111111111111111111', Output: '%b'\n", 2147483647); // Max binary
    my_printf("=====================================================================================================\n");



    // Reverse String Tests
    my_printf("Test Reverse Normal: Expected: 'olleH', Output: '%r'\n", "Hello");
    my_printf("Test Reverse Empty: Expected: '', Output: '%r'\n", "");
    my_printf("Test Reverse Null: Expected: '(null)', Output: '%r'\n", NULL);
    my_printf("Test Reverse kinda palindrome: Expected: 'Racecar', Output: '%r'\n", "racecaR");
    my_printf("Test Reverse Special Characters: Expected: '&*$#', Output: '%r'\n", "#$*&"); // Special characters
    my_printf("=====================================================================================================\n");




    // Uppercase String Tests
    my_printf("Test Uppercase Normal: Expected: 'WORLD', Output: '%u'\n", "world");
    my_printf("Test Uppercase Mixed: Expected: 'HELLO123', Output: '%u'\n", "hElLo123");
    my_printf("Test Uppercase Empty: Expected: '', Output: '%u'\n", "");
    my_printf("Test Uppercase Null: Expected: '(null)', Output: '%u'\n", NULL);
    my_printf("Test Uppercase Mixed Case: Expected: 'MIXCASE', Output: '%u'\n", "mixcaSE");
    my_printf("=====================================================================================================\n");



    // Character Tests
    my_printf("Test Character Simple: Expected: 'A', Output: '%c'\n", 'A');
    my_printf("Test Character Padded: Expected: '    B', Output: '%5c'\n", 'B');
    my_printf("Test Character Zero Width: Expected: 'Z', Output: '%c'\n", 'Z');
    my_printf("=====================================================================================================\n");



    // String Tests
    my_printf("Test String Normal: Expected: '       Hi!', Output: '%10s'\n", "Hi!");
    my_printf("Test String Short: Expected: 'Hi!', Output: '%2s'\n", "Hi!");
    my_printf("Test String Exact Width: Expected: 'Hey', Output: '%3s'\n", "Hey");
    my_printf("Test String Null: Expected: '(null)', Output: '%8s'\n", NULL);
    my_printf("Test String Empty: Expected: '', Output: '%5s'\n", "");
    my_printf("Test String Long Input: Expected: 'LongStringTest', Output: '%s'\n", "LongStringTest"); // Long input
    my_printf("=====================================================================================================\n");



    // Mixed Formatting Tests
    my_printf("Test Mixed Formatting: Expected: '   42 |      ff |     X |    Mixed!', Output: '%5d | %8x | %5c | %10s'\n", 42, 255, 'X', "Mixed!");
    my_printf("=====================================================================================================\n");


    // Edge Case Tests
    my_printf("Test Large Decimal: Expected: '2147483647', Output: '%d'\n", 2147483647); // INT_MAX
    my_printf("Test Small Decimal: Expected: '-2147483648', Output: '%d'\n", -2147483648); // INT_MIN
    my_printf("Test Large Hexadecimal: Expected: 'ffffffff', Output: '%x'\n", 4294967295U); // UINT_MAX
    my_printf("Test Large Binary: Expected: '1111111111111111', Output: '%b'\n", 65535);
    my_printf("=====================================================================================================\n");

    //error tests?
    int result = my_printf(NULL); // Passing NULL to simulate an error
    my_printf("Result: %d (Expected: -1 for null format string)\n", result);

    int test2 = my_printf("This is invalid: %q\n"); // Invalid specifier %q
    my_printf("Result: %d (Expected: character count for 'This is invalid: %%q\\n')\n", test2);

    int test3 = my_printf("%1d\n", INT_MAX); // INT_MAX needs more than 1 space
    my_printf("Result: %d (Expected: -1 for buffer overflow)\n", test3);





    my_printf("===== Tests Completed =====\n");
    // TESTTTTTTTTTT

    return 0;
}
