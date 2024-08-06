ldm (Load more) and stm (Store more)

Syntax:
    ldm src, {reglist}
    stm dst, {reglist}

Example:
    ldm r0, {r5-r6} === Think of it as an array, load first 4 bytes of address pointed to by r0 into r5, increment by 4 and then r6
    stm r0, {r5-r6} === Load value of r5 at the address of r0 and then r6 at r0 + 4
