#include <stdint.h>
#include "led.h"

#define STM32L475xx //c'est où se trouve le typedef GPIO
#include "stm32l4xx.h"  //on doit incluire le fichier pour l'utiliser

/*
#define RCC_AHB2ENR (*(volatile uint32_t *) (0x40021000 + 0X4C)) //page 83 de manual
#define GPIOB_MODER (*(volatile uint32_t *) (0x48000400))
#define GPIOB_BSSR (*(volatile uint32_t *) (0x48000400 + 0x18))
#define GPI0B_OSPEEDR (*(volatile uint32_t *) (0x48000400 + 0x08)) //on a besoin de vitesse très rapide

#define RCC_AHB2ENR_C (*(volatile uint32_t *) (0x40021000 + 0X4C))
#define GPIOC_MODER (*(volatile uint32_t *) (0x48000800)) //page 82 de manual
#define GPIOC_BSSR (*(volatile uint32_t *) (0x48000800 + 0x18))//page 82 de manual
*/

void led_init(){
    //Pour activer l'horloge du port B dans registre idoine
  //  uint32_t v= RCC_AHB2ENR;
  //  v= v | (1<<1);
  //  RCC_AHB2ENR=v;
    RCC->AHB2ENR |= (1<<1);

    //Pour configurer la broche PB14 en sortie
    GPIOB->MODER |= (1<<28);
    GPIOB->MODER &= ~ (1<<29);

    //LED3 YELLOW - LED 4 BLUE du port c
    RCC->AHB2ENR |= (1<<2);

    //Pour configurer la vitesse (11 very high speed), c'est pas trés necessaire
//    GPI0B_OSPEEDR |=(1<<28);
//    GPI0B_OSPEEDR |=(1<<29);
}

void led_g_on(){
    GPIOB->BSRR = (1<<14); //activer position 14

}

void led_g_off(){
    GPIOB->BSRR = (1<<14+ 16); // 14+16=30 pour activer le reset de 14

}

void led(state stateled ){ //sateled pour changer de state LED_OFF , LED_YELLOW, LED_BLUE
    if( stateled == LED_OFF)
    {
        GPIOC->MODER &= ~(1<<18);
        GPIOC->MODER &= ~(1<<19);//configurer en entrée
    }else{
        if (stateled == LED_YELLOW)
        {
            GPIOC->MODER |= (1<<18);
            GPIOC->MODER &= ~(1<<19);//configurer en sortie
            GPIOC->BSRR = (1<<9);//activer position 9 (set)
        }else{
            if (stateled == LED_BLUE)
            {
                GPIOC->MODER |= (1<<18);
                GPIOC->MODER &= ~(1<<19);//configurer en sortie
                GPIOC->BSRR = (1<<25);//activer position 9+16 (reset)
            }
        }
    }
}
