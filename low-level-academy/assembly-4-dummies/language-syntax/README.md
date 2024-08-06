

SYNTAX:
    operand dest, r1, r2
    example: ADD r0, r1, r2    === operation ADD to destination r0, add r1 and r2 together

    r2 / operand2 CAN be a register, an immediate value (like #4 is number 4) or a shifted register value ([])

    Immediate value:
        ADD R0, R1, #10 ; R0 = R1 + 10

    [] notation, usually performed with LDR operation (loads a value from the memory address)

    LDR R0, [R1, #4] ; R0 = *(R1 + 4)

    STR instruction stores a value from a register into a memory
    baiscally the opposite of LDR, takes value from R0 and stores it into memory adress obtained from R1 + 4

    STR R0, [R1, #4] ; *(R1 + 4) = R0

COMPILE:
    arm-linux-gnueabihf-gcc -o myfirst myfirst.s -nostdlib -static

    RUN:
        qemu-arm -g 4242 ./infinite_loop
    GDB:
        gdb-multiarch
        file ./myfirst
        target remote localhost:4242
        lay next
        ni

        
