.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
    ldr sp, =start_sp//mis addr dans sp,  0x10008000
    bl init_bss //mettre bss en 0
    bl main // appeler le main

_exit: // boucle infinie d'EXIT
b _exit