#ifndef LED_H
#define LED_H

typedef enum {LED_OFF, LED_YELLOW, LED_BLUE} state; //pour declarer stateled

// Functions declaration
void led_init();
void led_g_on();
void led_g_off();
void led(state stateled);
#endif