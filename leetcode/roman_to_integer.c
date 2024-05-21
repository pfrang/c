// Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
//
// Symbol       Value
// I             1
// V             5
// X             10
// L             50
// C             100
// D             500
// M             1000
// For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as XII, which is simply
// X + II. The number 27 is written as XXVII, which is XX + V + II.
//
// Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII.
// Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same
// principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:
//
// I can be placed before V (5) and X (10) to make 4 and 9.
// X can be placed before L (50) and C (100) to make 40 and 90.
// C can be placed before D (500) and M (1000) to make 400 and 900.
// Given a roman numeral, convert it to an integer.
#include <stdio.h>

typedef struct {
    char *key;
    int value;
} KeyValuePair;

KeyValuePair lookupTable[] = {{"A", 10}, {"B", 20}, {"C", 30}, {"D", 40}, {"L", 50}};

#define TABLE_SIZE (sizeof(lookupTable) / sizeof(KeyValuePair))

int romanToInt(char *s) {
    int result = 0;
    while (*s) {
        if (*s == 'I') {
            if (*(s + 1) == 'V') {
                result += 4;
                s++;
            } else if (*(s + 1) == 'X') {
                result += 9;
                s++;
            } else {
                result += 1;
            }
        } else if (*s == 'V') {
            result += 5;
        } else if (*s == 'X') {
            if (*(s + 1) == 'L') {
                result += 40;
                s++;
            } else if (*(s + 1) == 'C') {
                result += 90;
                s++;
            } else {
                result += 10;
            }
        } else if (*s == 'L') {
            result += 50;
        } else if (*s == 'C') {
            if (*(s + 1) == 'D') {
                result += 400;
                s++;
            } else if (*(s + 1) == 'M') {
                result += 900;
                s++;
            } else {
                result += 100;
            }
        } else if (*s == 'D') {
            result += 500;
        } else if (*s == 'M') {
            result += 1000;
        }
        s++;
    }
    return result;
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Number required");
        return -1;
    }

    char *input = argv[1];
    printf("Input %s\n", input);

    int roman = romanToInt(input);
    printf("Is roman %d", roman);
    return 0;
}
