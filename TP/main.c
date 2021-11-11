#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"

int x=0;

int fibo(int n){ //Function Fibonnacci
    int a = 0;
    int b= 1;
    int c;

    for(int i= 0; i<= n; i=i+1)
    {
        c= a + b;//c=0+1;c=1+1;c=1+2
        a=b;//a=1;a=1,a=2,
        b=c;//b=1,b=2;b=3,
    }

    return a;
}

int checksum(){
uint32_t sum = 0;
for (int i = 0; i<1000; i++){
    sum = uart_getchar() + sum;
}
return sum;
}

int main(){ //function main qui fait boucle infinite

    clocks_init(); // on doit appeler l'inisialitation de l'horloge
    led_init();
    uart_init();
    uart_puts("Hello World!");
    matrix_init();
    irq_init();
    button_init();

    while(1) //boucle infinite
    {
        test_pixels();
    }
}

