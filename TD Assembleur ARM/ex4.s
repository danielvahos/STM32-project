/*  DANIEL VAHOS M

    Exercice 4 de TD Assembleur ARM
    BONJOUR LE MONDE!
*/
.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:

    ldr r0, =0x10008000  //definir stack pointer
    mov sp, r0 ///definir stack pointer

	mov r0, pt_string // defino el t_string
    ldr r2, =0x10000300  // initial destin address
    bl memset
    mov r1, r0 // assign r1 as the string size
    bl mem_plusieurs



    mov r0, pt_string
    bl memcpy
    //mov r2, #0x0000300 // new address
    //mov r5, r1 // r5 becomes size of string
    bl mem_plusieurs

// r1 -- offset
// r3 -- motif
// r0 -- origin address

memset:
    mov r1, #0 //offset
    push {r4} //save on stack
    mov r4, #0 //0, it'll be the comparison "0" 
loop:
	ldrb r3, [r0,r1] // assign each letter in r3
    add r1,r1,#1 // r1 = r1 + 1
	cmp r3,r4 // if r3(letter) == r4/0 ?
	bne loop  //if no (z=0) --> repeat loop
    mov r0, r1 //if yes, assign r0 as the size (of the string)
    pop {r4} //return r4
    bx lr

//r1 -- offset
//r3 --- motif
//r0 --- origin address
//r2 -- destination address

//To copy the string
memcpy:
    push{r5}
    mov r5, #0 //offset
cploop: 
	ldrb r3, [r0,r5] // r3 = pt_string + r5(0)
    strb r3, [r2, r5] //store in destinationa address
    add r5,r5,#1 // r5 = r5 + 1
	cmp r5,r4 // if r5 == r4/size of string ?
	bne cploop  //if no (z=0) --> repeat loop
    //mov r1, r4 //r1 becomes size of string
    pop{r5} //return r5
    bx lr

//r0 --- origin 
// r2 -- destination
//r6 --number of times of copying (I chose it)

//To do it many(r6) times
mem_plusieurs:
    push{r4,r6}
    mov r4, r1 //r4 becomes size of string
    mov r6, #5 //number of times of copying (I chose it)
    
    bl memcpy

    add r2, r4,r2 // destin address = size of string + destin address 
    add r1,r1,#1 // r1 = r1 + 1
	cmp r1,r6 // if r1 == times of copying ?
	bne memcpy  //if no (z=0) --> repeat copy
    pop{r4,r6}
    bx lr

pt_string .word t_string
.section .rodata
t_string: asciz "Bonjour le monde!"

end: b end 