/* 
	DANIEL VAHOS M

	Exercise 2 de TD Assembleur ARM 

    r0 --> 0x10000000   start address
	r3 --> 0x10000300  new address

    r1 --> 0xdeadbeef   the pattern (le motif)
	r2 --> la taille 
    	La taille de la zone mémoire 0x100 octets (64 mots)

*/
.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

// r1 -- le motif
// r0 -- origin address
// r3 -- destination address

_start:
	ldr r0, =0x10000000  // defino direccion
	LDR r1, =0xdeadbeef  // defino el motivo 
	push {r4} //save r4 on stack
	mov r4, #0 // offset
	LDR r2, =0x100  // el tamaño de la zona memoria (256)
	ldr r3, =0x10000300 // defino direccion nueva pos

loop: 
	str r1, [r0,r4] // 0xdeadbeef = 0x10000000 + r2(0)
	add r4,r4,#4 // r4 = r4 + 4
	cmp r4,r2 // if r4 == r2/0x100 ?
	bne loop  //if no (z=0) --> repeat loop
	mov r4, #0 //initialize offset
	
cploop: 
	ldr r1, [r0,r4] // 0xdeadbeef = 0x10000000 + r4(0)
    str r1, [r3, r4] //copy to the new address
    add r4,r4,#4 // r4 = r4 + 4, advance by 4 bytes
	cmp r4,r2 // if r4(offset) == r2/0x100 ?
	bne cploop  //if no (z=0) --> repeat loop
	
	pop{r4} //restore r4

end: b end 
