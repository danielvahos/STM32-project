MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000 , LENGTH = 1M
    SRAM1 (wx) : ORIGIN = 0x20000000 , LENGTH = 96K
    SRAM2 (wx) : ORIGIN = 0x10000000 , LENGTH = 32K
}

SECTIONS
{
    .text : { /* Le code */
            *(.text)
    } >SRAM1

    .rodata : { /* Les constantes*/
            *(.rodata)
    } >SRAM1

    .data : { /* Les données initialisées*/
            *(.data)
    } >SRAM1

    .bss : { /* Les données non initialisées ou à zéro*/
            *(.bss) *(COMMON)
    } >SRAM1
}

ENTRY(main)