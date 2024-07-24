#include <stdio.h>
#include <string.h>

void vulnerableFunction(char *input) {
    char buffer[10];
    strcpy(buffer, input); // This is where the overflow can occur
    printf("Buffer content: %s\n", buffer);
    gets(buffer);
}

int main() {
    char longInput[] = "This input is definitely too long for the buffer!";
    vulnerableFunction(longInput);
    return 0;
}
