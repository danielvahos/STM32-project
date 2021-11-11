MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000 , LENGTH = 1M
    SRAM1 (wx) : ORIGIN = 0x20000000 , LENGTH = 96K
    SRAM2 (wx) : ORIGIN = 0x10000000 , LENGTH = 32K
}

SECTIONS
{
    .VECTOR_TABLE : ALIGN(256){
        *(.VECTOR_TABLE)
    } >SRAM1

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
                _bstart = . ;
            *(.bss) *(COMMON)
            _bend = . ;

    } >SRAM1
}
start_sp = ORIGIN(SRAM2) + LENGTH(SRAM2);
ENTRY(_start)