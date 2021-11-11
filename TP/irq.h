#ifndef IRQ_H
#define IRQ_H
#include "stm32l475xx.h"
#include <stdint.h>
#include "core_cm4.h" //pour trouver VTOR
#include "stm32l4xx.h"

extern uint8_t _start, start_sp;

#define MAKE_DEFAULT_HANDLER(interruption)\
    void __attribute__((weak)) interruption() {\
        __disable_irq();\
        while(1){}\
    }

void irq_init(void);

#endif