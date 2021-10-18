#include "led.h"
#include "clocks.h"

//int n;
//n = 8;
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


int main(){ //function main qui fait boucle infinite

    clocks_init(); // on doit appeler l'inisialitation de l'horloge
    led_init(); // I call the led_init function from led.c
    led_g_on(); // I order the led to turn on

    for (int i=0; i<3; i++){ //delay for being on
        asm volatile("nop");
    }

    led_g_off(); //I order the led to turn off

    for (int i=0; i<3; i++){// delay for being off
        asm volatile("nop");
    }

    led(LED_BLUE); //order the led blue/yellow to turn on/off

    for (int i=0; i<3; i++){// delay for being off
        asm volatile("nop");
    }
    led(LED_YELLOW);

    for (int i=0; i<3; i++){// delay for being off
        asm volatile("nop");
    }

    int result= fibo(8);
    return result;
    /*
    while(1) //boucle infinite
    {}
    */
}