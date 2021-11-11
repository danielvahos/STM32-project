#include "timer.h"

void timer_init(int max_us){
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
}