/* DANIEL VAHOS M

Exercise 1 

    ro --> 0x100   start adress

    r1 --> 0xdeadbeef   the pattern (le motif)

    La taille de la zone mémoire 0x100 octets (64 mots)

*/
.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
	ldr r0, =0x100  // defino direccion
	LDR r1, =0xdeadbeef  // defino el motivo 
	LDR r2, =0 // offset
	LDR r3, =0x100  // la taille de la zone mémoire

loop: 
	str r1, [r0,r2] // 0xdeadbeef = 0x100 + r2(0)
	add r2,r2,#4 // r2 = r2 + 4
	cmp r2,r3 // if r2 == r3/0x100 ?
	bne loop  //if no (z=0) --> repeat loop

end: b end 
