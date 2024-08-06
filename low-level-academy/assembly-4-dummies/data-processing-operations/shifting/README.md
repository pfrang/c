To investigate bit shift and math operations

Compile with: arm-linux-gnueabihf-gcc -o shift shift.c -static

Instructions:
    lsl = Logical shift left
    lsr = Logical shift right
    asr = Arithmetic shift right

    It shifts all bits in the register.
    Difference between arithmetic shift and logical shift is that arithmetic shift keeps the sign of the number (unsigned)

The additional s you will see in objdump, like lsrs and asrs is to simply state that

Sytntax:
    LSL dst_reg, src_reg, #<shift_amount>

Look at objdump: arm-linux-gnueabihf-objdump -d ./shift | less

The program's objdump:

    In this program you will see the instruction 'lsls r3, r3, #1' which is basically x = x * 2 because it shifts all bits once, hence #1, to the left in the existing registry. ls stands for logical shift
    For xx = xx *4 you will see 'lsls r3, r3, #2' to indicate moving bits twice (while for 8 it would be #3 )

    For the division, x = x /2, you will see 'asrs r3, r3, #1' shifting it to the right by 1
