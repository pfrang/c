// g++ -o outputfile.exe main.c && ./outputfile.exe
// to see outputed bytes objdump -d outputfile
#include <stdio.h>

int main() {
    printf("Hello World!\n");
    char s = 's';
    char *p = &s;

    printf("%c\n", *p);
}
