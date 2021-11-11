#ifndef UART_H
#define UART_H
#include <stdint.h>
#include <stddef.h>
#define STM32L475xx //c'est où se trouve le typedef
#include "stm32l4xx.h"  //on doit incluire le fichier pour l'utiliser
// Functions declaration
void uart_init(int baudrate);
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
void uart_puts(const char *s);
void uart_gets(char *s, size_t size);

#endif