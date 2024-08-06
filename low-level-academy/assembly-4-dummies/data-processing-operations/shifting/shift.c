#include <stdio.h>

// compile with arm-linux-gnueabihf-gcc -o shift shift.c -static

int main() {
    int x = 1; // signed by default
    unsigned int xx = 1;

    x = x * 2;
    xx = xx * 4;

    printf("%d, %u\n", x, xx);

    x = x / 2;

    printf("%d\n", x);
}
