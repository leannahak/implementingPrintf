
// used libraries
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "try.c"

// Error codes
#define success 0
#define nullPointerError 1
#define bufferSizeError 2

// defining limits for testing
#define INT_MIN (-2147483648)
#define INT_MAX (2147483647)

int my_printf(const char *input, ...);


// Main function with tests
int main() {
    my_printf("===== Testing my_printf =====\n");

    // Integer Conversion Tests
    my_printf("Test Integer Positive: Expected: '  123', Output: '%5d'\n", 123);
    my_printf("Test Integer Negative: Expected: ' -123', Output: '%5d'\n", -123);
    my_printf("Test Integer Zero: Expected: '    0', Output: '%5d'\n", 0);
    my_printf("Test Integer No Width: Expected: '456', Output: '%d'\n", 456);
    my_printf("Test Integer Zero Padding: Expected: '00042', Output: '%05d'\n", 42);
    my_printf("Test Integer Large Positive: Expected: '2147483647', Output: '%d'\n", INT_MAX); // Largest positive integer
    my_printf("Test Integer Small Negative: Expected: '-2147483648', Output: '%d'\n", INT_MIN); // Smallest negative integer
    my_printf("=====================================================================================================\n");


    // Hexadecimal Conversion Tests
    my_printf("Test Hex Positive: Expected: '000000ff', Output: '%08x'\n", 255);
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
    // here we are using style of printf that empty string gets padding
    my_printf("Test String Empty: Expected: '     ', Output: '%5s'\n", "");
    my_printf("Test String Long Input: Expected: 'LongStringTest', Output: '%s'\n", "LongStringTest"); // Long input
    my_printf("=====================================================================================================\n");



    // Mixed inputting Tests
    my_printf("Test Mixed inputting: Expected: '   42 |      ff |     X |    Mixed!', Output: '%5d | %8x | %5c | %10s'\n", 42, 255, 'X', "Mixed!");
    my_printf("=====================================================================================================\n");


    // Edge Case Tests
    my_printf("Test Large Decimal: Expected: '2147483647', Output: '%d'\n", 2147483647); // INT_MAX
    my_printf("Test Small Decimal: Expected: '-2147483648', Output: '%d'\n", -2147483648); // INT_MIN
    my_printf("Test Large Hexadecimal: Expected: 'ffffffff', Output: '%x'\n", 4294967295U); // UINT_MAX
    my_printf("Test Large Binary: Expected: '1111111111111111', Output: '%b'\n", 65535);
    my_printf("=====================================================================================================\n");

    //error tests
    int result = my_printf(NULL); // Passing NULL to simulate an error
    my_printf("Result: %d (Expected: -1 for null input string)\n", result);

    int test2 = my_printf("This is invalid: %q\n"); // Invalid specifier %q
    my_printf("Result: %d (Expected: character count for 'This is invalid: %%q\\n')\n", test2);

    int test3 = my_printf("%1d\n", INT_MAX); // INT_MAX needs more than 1 space
    my_printf("Result: %d (Expected: -1 for buffer overflow)\n", test3);

    my_printf("Test Large Decimal: Expected: '2147483647', Output: '%d'\n", 2147483647); // INT_MAX

    int overflow1 = my_printf("%1d\n", INT_MIN); // INT_MIN needs more than 1 space
    my_printf("Result: %d (Expected: -1 for buffer overflow)\n", overflow1);

    my_printf("Test Unsupported Specifier: Expected: 'This is invalid: %%z', Output: 'This is invalid: %%z'\n");

    my_printf("=================================================================================================\n");
    my_printf("===== Testing my_printf with Flags =====\n");

    // Integer Tests
    my_printf("Test Positive Integer: Expected: '+123', Output: '%+d'\n", 123);
    my_printf("Test Negative Integer: Expected: '-456', Output: '% d'\n", -456);
    my_printf("Test Space Flag: Expected: ' 789', Output: '% d'\n", 789);
    my_printf("Test Left Align: Expected: '42    ', Output: '%-6d'\n", 42);
    my_printf("Test Zero Padding: Expected: '00007', Output: '%05d'\n", 7);

    // Hexadecimal Tests
    my_printf("Test Alternate Hex: Expected: '0xff', Output: '%#x'\n", 255);
    my_printf("Test Zero Padding Hex: Expected: '00000010', Output: '%08x'\n", 16);
    my_printf("Test Left Align Hex: Expected: '1f      ', Output: '%-8x'\n", 31);

    // Binary Tests
    my_printf("Test Binary Small: Expected: '111', Output: '%b'\n", 7);
    my_printf("Test Binary Large: Expected: '11111111', Output: '%#b'\n", 255);
    my_printf("Test Binary Padding: Expected: '     101', Output: '%08b'\n", 5);

    // Reverse String Tests
    my_printf("Test Reverse String: Expected: 'olleh', Output: '%r'\n", "hello");
    my_printf("Test Reverse Null: Expected: '(null)', Output: '%r'\n", NULL);

    // Uppercase String Tests
    my_printf("Test Uppercase String: Expected: 'HELLO', Output: '%u'\n", "hello");
    my_printf("Test Uppercase Null: Expected: '(null)', Output: '%u'\n", NULL);

    // Character Tests
    my_printf("Test Character: Expected: 'A', Output: '%c'\n", 'A');
    my_printf("Test Character with Padding: Expected: '     B', Output: '%5c'\n", 'B');

    // String Tests
    my_printf("Test String: Expected: 'Hi!', Output: '%s'\n", "Hi!");
    my_printf("Test String with Width: Expected: '       Hi!', Output: '%10s'\n", "Hi!");
    my_printf("Test String Left Align: Expected: 'Hi!       ', Output: '%-10s'\n", "Hi!");

    // Mixed Tests
    my_printf("Test Mixed: Expected: '  +42 |    0xff | Mix       ', Output: '%+5d | %#8x | %-10s'\n", 42, 255, "Mix");

    // Complex Flag Combinations
    my_printf("Test Flags + Width (Integer): Expected: '+0042', Output: '%+05d'\n", 42);
    my_printf("Test Flags + Width (Hex): Expected: '0x00001f', Output: '%#08x'\n", 31);
    my_printf("Test Special Characters: Expected: '!@#$%^&*()', Output: '%s'\n", "!@#$%^&*()");
    my_printf("Test Large Width (Integer): Expected: '          42', Output: '%12d'\n", 42);

    my_printf("=====================================================================================================\n");


    my_printf("===== Tests Completed :)  ======\n");


    return 0;
}
