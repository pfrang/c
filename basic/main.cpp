// g++ -o outputfile.exe main.c && ./outputfile.exe
// to see outputed bytes objdump -d outputfile
// generate to new file gcc -S your_file.c
#include <stdio.h>

void arrayIndexing(void);

struct projectile {
    char unsigned IsThisOnFire;
    int Damage;
    int ParticlesPerSecond;
    short HowManyCooks;

    // Would expect memory alloc for this strict to be 1 byte + 4 bytes + 4
    // bytes + 2 bytes = 11, but it reserves 4 bytes for each var, 16
};

int main(void) {
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

    // arrayIndexing();

    // accessing members of a struct pointer vs value

    projectile TestPointer2;  // When its referencing a value / an actual thing on the stack
    TestPointer2.Damage = 5;  // with dot (.)
    // THese are the same
    projectile *TestPointer3 = &TestPointer2;
    TestPointer3->Damage = 6;  // I haven now changed Testpointer2's value to 6
    printf("%d \n", TestPointer2.Damage);
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
