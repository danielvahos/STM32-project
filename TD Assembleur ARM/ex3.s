/*  
    DANIEL VAHOS M
    Exercise 3 de TD Assembleur ARM

    r0 --> 0x10000000   start address
    r3 --> 0x10000300  new address

    r1 --> 0xdeadbeef   the pattern (le motif)

    La taille de la zone mémoire 0x100 octets (64 mots)

*/
.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
	ldr r0, =0x10000000  // defino direccion
	LDR r1, =0xdeadbeef  // defino el motivo
	LDR r2, =0x100  // el tamaño de la zona memoria
    LDR r3, = 0x10000300  // la otra direccion
    bl memset
    bl memcpy

// r1 -- le motif
// r0 -- origin address
// r3 -- destination address

memset:
    push{r4} //save r4 on stack
    mov r4, #0  //define as offset
loop:
	str r1, [r0,r4] // 0xdeadbeef = 0x10000000 + r4(0)
    add r4,r4,#4 // r4 = r4 + 4, advance by 4 bytes
	cmp r4,r2 // if r4(offset) == r2/0x100 ?
	bne loop  //if no (z=0) --> repeat loop
    pop{r4} //return r4
    bx lr

memcpy:
    push{r4} //save r4 on stack   
    mov r4, #0 //define as offset
cploop: 
	ldr r1, [r0,r4] // 0xdeadbeef = 0x10000000 + r4(0)
    str r1, [r3, r4] //copy to the new address
    add r4,r4,#4 // r4 = r4 + 4, advance by 4 bytes
	cmp r4,r2 // if r4(offset) == r2/0x100 ?
	bne cploop  //if no (z=0) --> repeat loop
    pop{r4} //return r4
    bx lr

end: b end 