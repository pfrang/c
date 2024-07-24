#include <stdio.h>
#include <string.h>

void blablabla(char *);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Need to pass second arg\n");
        return -1;
    }

    blablabla(argv[1]);
    return 0;
}

void blablabla(char *input) {
    char buffer[10];
    strcpy(buffer, input);
    printf("Buffer content: %s\n", buffer);
}
