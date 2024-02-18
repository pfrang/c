// g++ -o outputfile.exe main.c && ./outputfile.exe
// to see outputed bytes objdump -d outputfile
// generate to new file gcc -S your_file.c
#include <stdio.h>
#include <string.h>

void arrayIndexing(void);
void bitOperators(void);
void logicalOperators(void);
void loops(void);
unsigned long switchHustler(char *input);
void pointers(void);

struct projectile {
    char unsigned IsThisOnFire;
    int Damage;
    int ParticlesPerSecond;
    short HowManyCooks;

    // Would expect memory alloc for this strict to be 1 byte + 4 bytes + 4
    // bytes + 2 bytes = 11, but it reserves 4 bytes for each var, 16
};

// can take in terminal arguments
int main(int argc, char *argv[]) {
    if (argc < 2) {  // The first argument is the program name
        int i = 0;
        char input;
        printf("Enter a char: ");
        scanf("%c", &input);

        printf("%c \n", input);
        printf("No arguments \n");
        return 0;
    };

    // char *input = &argv[1][0];

    char *input = argv[1];

    printf("%p \n", input);
    printf("%s \n", input);

    switch (switchHustler(input)) {  // switch only JUMPS to the first true case, and then executes all the code below. It needs to break in order to exit
        case 1:
            loops();
            break;
        case 2:
            arrayIndexing();
            break;
        case 3:
            bitOperators();
            break;
        case 4:
            pointers();
            break;
        default:
            printf("default \n");
            break;
    }

    char input2[] = "hello2";

    // unsigned long hei = switchHustler();
    // return 0;
    // arrayIndexing();
    // bitOperators();
    // pointers();
    // loops();
}

unsigned long switchHustler(char *input) {
    int i;

    for (i = 0; i < sizeof(input); i++) {
        printf("%c \n", input[i]);
    }

    if (strcmp(input, "loops") == 0) {
        return 1;
    } else if (strcmp(input, "index") == 0) {
        return 2;
    } else if (strcmp(input, "bit") == 0) {
        return 3;
    } else if (strcmp(input, "pointers") == 0) {
        return 4;
    } else {
        return 0;
    }
}

void pointers(void) {
    char unsigned s = 's';  // 8 bits - 2^8 = 256 different values - [-128, 127]
    char unsigned SmallU;   // 8 bits - 2^8 = 256 diffetrent values - [0, 255]
    short MediumS = 16;     // 16 bits - 2^16 = 65536
    int LargeS;             // 32 bits - 2^32 = 4294967296

    char unsigned *sPointer;
    sPointer = &s;

    char unsigned Overflow;

    Overflow = 124;
    Overflow = Overflow + 1;  // Now Overflow is 0 - will overflow
    printf("%d \n", Overflow);

    char unsigned *TestPointer;  // Holds addresses of variables
    TestPointer = &Overflow;     //  Assigns address of Overflow to TestPointer
    // print address
    printf("%p \n", TestPointer);   // %p is for pointers to print address
    printf("%d \n", *TestPointer);  // prints the value of the address

    // STRUCTS

    projectile Test;

    int sizeOfChar = sizeof(char unsigned);     // 1
    int sizeOfInt = sizeof(int);                // 4
    int sizeOfProjectile = sizeof(projectile);  // 16
    int sizeOfTest = sizeof(Test);              // 16

    Test.Damage = 2;
    Test.ParticlesPerSecond = 3;
    Test.HowManyCooks = 4;

    // accessing members of a struct pointer vs value

    projectile TestPointer2;  // When its referencing a value / an actual thing on the stack
    TestPointer2.Damage = 5;  // with dot (.)
    // THese are the same
    projectile *TestPointer3 = &TestPointer2;
    TestPointer3->Damage = 6;    // I haven now changed Testpointer2's value to 6
    (*TestPointer3).Damage = 7;  // -> is the same as (*)

    int *ptr = 0;
    int y = 5;
    if (y == 5) {
        int x = 6;
        int y = 4;
        ptr = &x;
    }

    // THIs is asking for trouble, should never allocate memory to in-scope variable
    *ptr = 7;  // this is the same as x = 7, but x is out of scope so its not recommended

    printf("%d \n", *ptr);  // 7

    int *ptr2 = 0;

    int y2 = (*ptr);  // DEREFERENCING - chasing the pointer

    printf("%d \n", y2);  // 7

    // Double pointer
    int y3 = 5;
    int *ptr4 = 0;
    int **ptrptr3 = 0;

    if (y3 == 5) {
        int x3 = 6;
        int y3 = 4;

        ptr4 = &x3;
        ptrptr3 = &ptr4;  // Pointer of a pointer to the adress of a pointer. This is a double pointer
    }

    y3 = (**ptrptr3);     // DEREFERENCING - since its referencing a pointer, we need to dereference twice. Chase the pointer's pointer
    printf("%d \n", y3);  // 6
    // THIs is asking for trouble, should never allocate memory to in-scope variable

    // to display inner block scoped vars

    int y4 = 5;
    int *ptr5 = 0;
    int *ptr6 = 0;

    ptr5 = &y4;

    if (y4 == 5) {
        int y4 = 4;
        ptr6 = &y4;
    }

    // printf memory address pointer
    printf("%p \n", ptr5);
    printf("%p \n", ptr6);
}

void arrayIndexing(void) {
    // allocate mmory for 40 projectile objects

    projectile Projectiles[40];  // they are placed in memory with an arbitrary
                                 // number of bytes between them, no logic
                                 // needed to access each index
    int whichProjectile = 4;
    Projectiles[whichProjectile];  // array indexing.
    // this is strange, pointers, declarated with * should only be able to store
    // addressess, declared with & before var assignment but when referencing an
    // array or struct/object, they are basically returning the memory of the
    // first byte, but C under the hood somehow magically translates the sizeOf
    // Projectiles to be the entire struct
    projectile *ProjectilePointer = Projectiles;

    // when investigating memory allocation for Pojectiles, the non-value assigned
    // variables/values will be given "garbage" values because that is the value
    // that memory already held
    // F.ex.The unsigned char which only needs 1 byte will only use 1 byte,
    // and since struct defines 4 bytes per variable regardless,
    // there will also be "garbage" values inbetween the vairables

    int sizeOfProjectiles = sizeof(Projectiles);              // 16 * 40;
    int sizeOfProjectilePointer = sizeof(ProjectilePointer);  // 8 (64 bits, 8 bits per byte)
    // array indexing and setting values
    Projectiles[30].Damage = 60;
    // THESE ARE THE SAME - what this translates to is ref code below
    (ProjectilePointer + 30)->Damage = 100;  // this is really (ProjectilePointer + 30*sizeof(pointer) to move
    // to the correct memory address, but C already does this automatically

    // to display "what really happens" to jump to the correct memory address
    // what is happening here is PojectilePointer is casted to a byte pointer
    // and then the size of a projectile is multiplied by 30 and added to the
    // address of ProjectilePointer, and then casted back to a projectile pointer
    ((projectile *)((char *)ProjectilePointer + 30 * sizeof(projectile)))->Damage = 100;

    // explained with multiple operatons below
    char *BytePointer = (char *)ProjectilePointer;          // set to byte pointer
    BytePointer = BytePointer + (30 * sizeof(projectile));  // move to correct memory address, counting bytes
    projectile *Thirty = (projectile *)BytePointer;         // cast back to projectile pointer
    // field would not be available in the regular byte pointer, but on casting and telling C we know that this memory address holds
    Thirty->Damage = 100;
    // our struct, we can cast it and let C chill enusring we are a "pro programmer"
}

void bitOperators(void) {
    // byte shifting
    // The expression 1 << 4 uses the bitwise left shift operator (<<).
    // This operator shifts the bits of the number on the left
    // (in this case 1), to the left by the number of positions
    // specified on the right (in this case 4).
    char unsigned Byt;     // 0
    Byt = (1 << 4);        // 16
    Byt = Byt + (1 << 4);  // 16

    char unsigned Byte = 1;  // 1
    Byte = Byte << 1;        // 2
    Byte = Byte << 1;        // 4
    Byte = Byte << 1;        // 8
    Byte = Byte << 1;        // 16
    Byte = Byte << 1;        // 32
    Byte = Byte << 1;        // 64
    Byte = Byte << 1;        // 128
    // Byte = Byte << 1;                 // 256 - overflow
    printf("%d \n", Byte);

    // set value by bite shifting

    char unsigned Byte2 = 0;  // 0

    // what | means is to execute the operation on the
    // When you perform a bitwise OR operation (|),
    // for each bit in the binary representation,
    // it combines all of the set bits
    // from both numbers to produce the final result.
    // If either or both bits are 1, the result is 1.
    // If both bits are 0, the result is 0.
    // 0 | 0 = 0
    // 0 | 1 = 1
    // 1 | 0 = 1
    // 1 | 1 = 1

    char unsigned Byte4;

    Byte4 = 1 | 2;  // 3
    // 1 | 2 = 3 (0001 | 0010 = 0011) = it keeps 1 in both checks
    Byte4 = 1 & 2;  // 0 (0001 & 0010 = 0000) = it keeps 0 in both checks

    printf("%d Byt4 \n", Byte4);

    Byte2 = Byte2 | (1 << 4);  // 16
    Byte2 = Byte2 | (1 << 8);  // 24
    Byte2 = Byte2 & (1 << 4);  // 16

    printf("%d \n", Byte2);

    // the ~ operator is a bitwise NOT operator.
    // it sets all the bits to the opposite of what they were. 0 to 1
    // and 1 to 0

    // MASKING

    Byte2 = 16;

    Byte4 = 7;
    // Only take the bit values that are equal to 1 in both
    // 0001 0000 = 16
    // 0000 0111 = 7
    // 0000 0000 & = 0
    // Byte2 is masking byte 4, only keeping the bits
    // that are 1 in both
    Byte2 = Byte2 & Byte4;  // 0

    char unsigned Byte3 = 0;  // 0
    Byte3 = ~Byte3;           // 255

    // this ^ is an xor operaotr
    // 1 ^ 1 = 0
    // 1 ^ 0 = 1
    // 0 ^ 1 = 1
    // 0 ^ 0 = 0
    int j = 2 ^ 3;  // in binary is 0010 ^ 0011 = 0001 = 1. When both bits are 1, return 0
    printf("%d j \n", j);
}

void logicalOperators(void) {
    // this a logical || operator, but it returns 1 if either is true, 0 if not
    int h = 2 || 3;
    printf("%d \n", h);

    // and this is a logical && operator, returns 1 if both is true
    int i = 2 && 3;
    printf("%d \n", i);
}

void loops(void) {
    int i = 0;
    // for loop
    for (i; i <= 10; i++) {
        printf("%d  \n", i);
    }

    // while loop
    int x = 0xa;               // 10
    int condition = (x != 0);  // 1
    while (x != 0) {
        x = x << 4;  // when shift operation pushes 1 out of the 32 bits, it is lost == 0
        printf("%d \n", i);
    }

    // with break statement
    x = 0xa;  // 10
    while (1) {
        printf("%d \n", x);
        if (x == 0) {
            break;
        }
        x = x << 4;
    }

    // do while loop

    do {
        printf("%d \n", i);
        i++;
    } while (i < 10);
}
