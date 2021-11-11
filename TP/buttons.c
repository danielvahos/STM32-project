#include "buttons.h"
#include "led.h"
#define STM32L475xx
#include "stm32l4xx.h"

void button_init(void){
    //Active l'horloge du port C
    SET_BIT(RCC->AHB2ENR,RCC_AHB2ENR_GPIOCEN);

    //Configure la broche PC13 en GPIO et en entrée
    GPIOC->MODER=( GPIOC->MODER &~GPIO_MODER_MODE13_1) &~ GPIO_MODER_MODER13_0;

    //Sélectionne la broche PC13 comme source d'IRQ pour EXTI13
    SYSCFG->EXTICR[3]=(SYSCFG->EXTICR[3] &~ SYSCFG_EXTICR4_EXTI13_Msk) | (SYSCFG_EXTICR4_EXTI13_PC);

    EXTI->RTSR1 =(EXTI->RTSR1 &~EXTI_RTSR1_RT13);
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM13);

    SET_BIT(EXTI->FTSR1, EXTI_FTSR1_FT13);
    NVIC_EnableIRQ(40);
}

//Fonction pour l'interruption dans l'EXTI
void EXTI15_10_IRQHandler(void){
    SET_BIT(EXTI->PR1, EXTI_PR1_PIF13);
    led_g_on();

    for (int i=0; i<100000; i++){
        asm volatile("nop");
    }
    led_g_off();
}

