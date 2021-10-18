// init.c pour mettre bss en 0
#include <stdint.h>

extern uint8_t  _bstart, _bend;

//uint8_t *dst = &_bstart;
//uint8_t *point= &_bend;

// Zero out bss
void init_bss(){
    for (uint8_t *dst = &_bstart; dst < &_bend; dst++)
        *dst = 0;
}
