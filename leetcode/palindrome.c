// Given an integer x, return true if x is a
// palindrome
// , and false otherwise.
//
//
//
// Example 1:
//
// Input: x = 121
// Output: true
// Explanation: 121 reads as 121 from left to right and from right to left.
// Example 2:
//
// Input: x = -121
// Output: false
// Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a
// palindrome. Example 3:
//
// Input: x = 10
// Output: false
// Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isOdd(int num) { return num % 2 != 0; }

bool isPalindrome(int num) {
    char str[50];

    sprintf(str, "%d", num);

    int len = strlen(str);
    if (len == 1)
        return true;

    int reallen;
    if (isOdd(len)) {
        reallen = (len + 1) / 2;
    } else {
        reallen = len / 2;
    }

    for (int i = 0; i < reallen; i++) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a number as a command line argument.\n");
        return 1;
    }

    int num = atoi(argv[1]);

    printf("You entered: %d\n", num);
    if (isPalindrome(num)) {
        printf("%d Is palindrome", num);
    }
}
