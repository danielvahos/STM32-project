.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
    ldr sp, =0x10008000 //mis addr dans sp
    bl init_bss
    bl main
    b _exit

_exit:
b _exit