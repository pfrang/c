#include <stdint.h>
#include <stdio.h>

uint32_t val = 0;

// arm-linux-gnueabihf-gcc -o ld ld.c
// arm-linux-gnueabihf-objdump -d ./ld | less

int main() { val = 32; }
