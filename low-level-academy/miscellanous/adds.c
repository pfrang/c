#include <stdio.h>

void bigvslittleendian(void);

int main() {
    int h = 0;
    int j = 2;

    int g = h + j;

    int b[6] = {1, 5342, 3, 4, 5, 6};

    // print the b array address
    printf("%p\n", b);

    printf("%d\n", *b);

    // increment by 1
    printf("%p\n", b + 1);

    // print whatever value is in that address
    printf("%d\n", *(b + 1));

    bigvslittleendian();
}

void bigvslittleendian(void) {
    int num = 0x12345678;
    unsigned char *byte_ptr = (unsigned char *)&num;

    printf("Memory representation of integer: ");
    for (int i = 0; i < sizeof(int); i++) {
        printf("%02x ", byte_ptr[i]);
    }
    printf("\n");
    printf("%d\n", num);

    int g = 8 + 112 + 1536 + 20480 + 262144 + 3145728 + 33554432 + 268435456;

    printf("%d\n", g);
}
