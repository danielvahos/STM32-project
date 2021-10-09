// init.c
#include <stdint.h>

extern char  _bstart, _bend;

uint8_t *dst = &_bstart;
uint8_t *point= &_bend;

// ROM has placed .data at end of .text.
// Copy .data to RAM
//while (dst < &_edata)
//    *dst++ = *src++;

// Zero out bss
void init_bss(){
    for (dst = &_bstart; dst < point; dst++)
        *dst = 0;
}
