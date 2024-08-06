Moving data:
    The LDR instruction is used to load a value form memory into a register.
    However, it is limited to 32 bytes, what happens if we try to read a bigger value.
    This is why LDR is a pseudo-instruction

    movw and movt are instructions that splits it up.
    movw moves the lower half first, then movt moes the top (must be in this order).
    To then move a 32-bit value they might be split up into 2 16-bit values because movt and movw takes 4 bits each (1 byte)

    32-bit Instruction Length: ARM instructions are typically 32 bits long, which must include the opcode, register specifiers, and any immediate value. This limits the number of bits available for immediate values.

LDR vs STR vds MOV:
    LDR loads a value from memory into register
    STR stores a value from register into memory
    MOV copies a value from register to register
    Syntax:
        ldr dst_reg, [address_register] / =#immediate_value
        str src_reg, [address_register]
        mov dst_reg, src_reg

PC-relative offset.
    To optimize, the compiler will often do this with [pc, #16] to indicate that jumps 16 bytes ahead of the program counter (insturction pipeline) to fetch some value stored in address to register

Compile:
    arm-linux-gnueabihf-gcc -o test test.s -nostdlib -static

Disassemble:
    arm-linux-gnueabihf-objdump -d ./ld | less OR
    arm-linux-gnueabihf-objdump -d ./ld > dump.txt

GDB:
    To see values corresponding to addresses in gdb, x/32x $register (ro)
