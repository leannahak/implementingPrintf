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
int my_printf(const char *input, ...) {
    if (!input) return -1; // Handle null input string

    va_list args;     // variable argument list
    va_start(args, input); // initialize that list

    int totalPrinted = 0; // Counter for the total characters printed, to ensure we handle errors like printf

    while (*input) {
        if (*input == '%') { // input specifier handling
            input++;

            int isLeftAlign = 0, isZeroPad = 0, showSign = 0, addSpace = 0, isAlternate = 0;
            while (*input == '-' || *input == '+' || *input == ' ' || *input == '0' || *input == '#') {
                if (*input == '-') isLeftAlign = 1;
                else if (*input == '+') showSign = 1;
                else if (*input == ' ') addSpace = 1;
                else if (*input == '0') isZeroPad = 1;
                else if (*input == '#') isAlternate = 1;
                input++;
            }
            if (isLeftAlign) isZeroPad = 0; // '-' overrides '0'

            // Parse width
            int width = 0; // field width for inputting
            while (*input >= '0' && *input <= '9') {
                width = width * 10 + (*input - '0'); // parse the width
                input++;
            }

            char buffer[128]; // buffer to hold output
            int result = success; // status for helper funcs

            switch (*input) {
                case 'd': {
                    int value = va_arg(args, int); // get argument
                    result = intToString(value, buffer, sizeof(buffer)); // Convert to string
                    if (result == bufferSizeError) return -1; // handle buffer overflow

                    if (result != success) return -1;

                    int len = strlen(buffer);

                    if (width > 0 && width < len) {
                        return -1; // Return error for buffer overflow
                    }

                    if (value >= 0 && showSign) { putchar('+'); totalPrinted++; }
                    else if (value >= 0 && addSpace) { putchar(' '); totalPrinted++; }

                    if (width > len) {
                        int padding = width - len - (value >= 0 && (showSign || addSpace));
                        if (isZeroPad && !isLeftAlign) {
                            for (int i = 0; i < padding; i++) { putchar('0'); totalPrinted++; }
                        } else if (!isLeftAlign) {
                            for (int i = 0; i < padding; i++) { putchar(' '); totalPrinted++; }
                        }
                    }

                    for (char *p = buffer; *p; p++) { putchar(*p); totalPrinted++; }

                    if (isLeftAlign && width > len) {
                        for (int i = len; i < width; i++) { putchar(' '); totalPrinted++; }
                    }
                    break;
                }
                case 'x': {
                    unsigned int value = va_arg(args, unsigned int); // Get argument
                    result = intToHex(value, buffer, sizeof(buffer)); // Convert to hex
                    if (result == bufferSizeError) return -1; // handle buffer overflow

                    if (result != success) return -1;

                    int len = strlen(buffer);
                    if (isAlternate && value != 0) {
                        putchar('0'); putchar('x'); totalPrinted += 2;
                    }

                    if (width > len) {
                        int padding = width - len - (isAlternate && value != 0 ? 2 : 0);
                        if (isZeroPad && !isLeftAlign) {
                            for (int i = 0; i < padding; i++) { putchar('0'); totalPrinted++; }
                        } else if (!isLeftAlign) {
                            for (int i = 0; i < padding; i++) { putchar(' '); totalPrinted++; }
                        }
                    }

                    for (char *p = buffer; *p; p++) { putchar(*p); totalPrinted++; }

                    if (isLeftAlign && width > len) {
                        for (int i = len; i < width; i++) { putchar(' '); totalPrinted++; }
                    }
                    break;
                }
                case 'b': {
                    unsigned int value = va_arg(args, unsigned int); //unsigned int argument
                    result = intToBinary(value, buffer, sizeof(buffer)); //convert to binary
                    if (result == bufferSizeError) return -1; // Handle buffer overflow

                    if (result != success) return -1; // Handle errors in intToBinary

                    int len = strlen(buffer);

                    if (width > len) {
                        int padding = width - len;
                        if (!isLeftAlign) {
                            for (int i = 0; i < padding; i++) { putchar(' '); totalPrinted++; }
                        }
                    }

                    for (char *p = buffer; *p; p++) { putchar(*p); totalPrinted++; }

                    if (isLeftAlign && width > len) {
                        for (int i = len; i < width; i++) { putchar(' '); totalPrinted++; }
                    }
                    break;
                }
                case 'r': {
                    char *str = va_arg(args, char *); // get str argument
                    if (!str) str = "(null)"; //null string case
                    strncpy(buffer, str, sizeof(buffer) - 1); //write it to buffer
                    buffer[sizeof(buffer) - 1] = '\0'; // null terminate
                    if (strcmp(str, "(null)") != 0) {
                        result = reverseString(buffer); //reverse the str
                        if (result != success) return -1; // Handle errors in reverseString
                    }

                    for (char *p = buffer; *p; p++) { putchar(*p); totalPrinted++; }
                    break;
                }
                case 'u': {
                    char *str = va_arg(args, char *); // Get str argument
                    if (!str) str = "(null)";// Handle null string

                    if (strcmp(str,"(null)") == 0) {
                        for (const char *p = str; *p; p++) {
                            putchar(*p);
                            totalPrinted++;
                        }

                    }else {
                        strncpy(buffer, str, sizeof(buffer) - 1);
                        buffer[sizeof(buffer) - 1] = '\0';
                        result = stringToUpper(buffer); //convert to upper
                        if (result != success) return -1; // handle errors

                        for (char *p = buffer; *p; p++) {
                            putchar(*p);
                            totalPrinted++;
                        }
                    }

                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int); //get the char argument

                    // handles output inputting for when width is specified
                    if (width > 1) {
                        int padding = width - 1;
                        char padChar = isZeroPad ? '0' : ' ';
                        if (!isLeftAlign) {
                            for (int i = 0; i < padding; i++) { putchar(padChar); totalPrinted++; }
                        }
                    }
                    putchar(c); totalPrinted++;

                    if (width > 1 && isLeftAlign) {
                        for (int i = 0; i < width - 1; i++) { putchar(' '); totalPrinted++; }
                    }
                    break;
                }
                case 's': {
                    char *str = va_arg(args, char *); //get str argument
                    if (!str) str = "(null)"; //null str handling
                    int len = strlen(str); // str length

                    if (strcmp(str, "(null)" ) == 0) {
                        // Skip width logic for NULL strings
                        for (const char *p = str; *p; p++) { putchar(*p); totalPrinted++; }
                    } else {
                        if (width > len && !isLeftAlign) {
                            for (int i = 0; i < width - len; i++) { putchar(' '); totalPrinted++; }
                        }

                        for (char *p = str; *p; p++) { putchar(*p); totalPrinted++; }

                        if (width > len && isLeftAlign) {
                            for (int i = 0; i < width - len; i++) { putchar(' '); totalPrinted++; }
                        }
                    }
                    break;
                }
                default: // handling the input specifiers not supported in this implementation
                    // regualr printf in c handles invalid specifiers in many diff ways depending on the situation so this is how i decided to work with it
                    putchar('%'); totalPrinted++;
                    putchar(*input); totalPrinted++;
                    break;
            }
        } else { // jsut print the characters regularly
            putchar(*input); totalPrinted++;
        }
        input++;
    }

    va_end(args);
    return totalPrinted; // return total # chars printed
}
