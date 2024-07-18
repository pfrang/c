#include <stdio.h>
#include <stdlib.h>

typedef enum { SUCCESS, NOT_SUCCESS } status_t;

status_t foo(int **data, int len) {
    int *temp = NULL;
    temp = realloc(*data, len);

    if (temp == NULL) {
        return NOT_SUCCESS;
    }

    *data = temp;
    return SUCCESS;
}

int main() {
    int *first = malloc(64);

    if (foo(&first, 128) == NOT_SUCCESS) {
        printf("uh oh\n");
        return -1;
    }

    return 0;
}
