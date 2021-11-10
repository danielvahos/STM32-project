#ifndef MATRIX_H
#define MATRIX_H
#include "stm32l4xx.h"
#include <stdint.h>

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;

rgb_color image_matrix[64];

extern rgb_color _binary_image_raw_start, _binary_image_raw_end;


//MACROS - CONTROLE DES BROCHES
//Port C
#define SB(x) ((x == 1) ? (GPIOC->BSRR= GPIO_BSRR_BS_5) : (GPIOC->BSRR=GPIO_BSRR_BR_5))
#define LAT(x) ((x == 1) ? (GPIOC->BSRR= GPIO_BSRR_BS_4) : (GPIOC->BSRR=GPIO_BSRR_BR_4))
#define RST(x) ((x == 1) ? (GPIOC->BSRR= GPIO_BSRR_BS_3) : (GPIOC->BSRR=GPIO_BSRR_BR_3))
//Port B
#define SCK(x) ((x == 1) ? (GPIOB->BSRR= GPIO_BSRR_BS_1) : (GPIOB->BSRR=GPIO_BSRR_BR_1))
#define ROW0(x) ((x == 1) ? (GPIOB->BSRR= GPIO_BSRR_BS_2) : (GPIOB->BSRR=GPIO_BSRR_BR_2))
#define ROW6(x) ((x == 1) ? (GPIOB->BSRR= GPIO_BSRR_BS_0) : (GPIOB->BSRR=GPIO_BSRR_BR_0))
//Port A
#define SDA(x) ((x == 1) ? (GPIOA->BSRR= GPIO_BSRR_BS_4) : (GPIOA->BSRR=GPIO_BSRR_BR_4))
#define ROW2(x) ((x == 1) ? (GPIOA->BSRR= GPIO_BSRR_BS_2) : (GPIOA->BSRR=GPIO_BSRR_BR_2))
#define ROW1(x) ((x == 1) ? (GPIOA->BSRR= GPIO_BSRR_BS_15) : (GPIOA->BSRR=GPIO_BSRR_BR_15))
#define ROW3(x) ((x == 1) ? (GPIOA->BSRR= GPIO_BSRR_BS_7) : (GPIOA->BSRR=GPIO_BSRR_BR_7))
#define ROW4(x) ((x == 1) ? (GPIOA->BSRR= GPIO_BSRR_BS_6) : (GPIOA->BSRR=GPIO_BSRR_BR_6))
#define ROW5(x) ((x == 1) ? (GPIOA->BSRR= GPIO_BSRR_BS_5) : (GPIOA->BSRR=GPIO_BSRR_BR_5))
#define ROW7(x) ((x == 1) ? (GPIOA->BSRR= GPIO_BSRR_BS_3) : (GPIOA->BSRR=GPIO_BSRR_BR_3))


//Functions declaration
void pulse_LAT();
void pulse_SCK();
void send_byte(uint8_t val, int bank);
void init_bank0();
void matrix_init();
void pulse_LAT();
void deactivate_rows();
void activate_row(int row);
void mat_set_row(int row, const rgb_color *val);
void test_pixels();

#endif