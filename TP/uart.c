#include "uart.h"
//#include "matrix.h"
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;
extern rgb_color image_matrix[64];
uint32_t cont= 0;
uint8_t pixel =0;


void uart_init(int baudrate){
    //Pour activer l'horloge du port B dans registre idoine
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    GPIOB-> MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7_Msk)  | (2 << GPIO_MODER_MODE7_Pos);
    GPIOB-> MODER = (GPIOB->MODER & ~GPIO_MODER_MODE6_Msk)  | (2 << GPIO_MODER_MODE6_Pos);

    GPIOB-> AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL6_Msk)  | (7 << GPIO_AFRL_AFSEL6_Pos);
    GPIOB-> AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL7_Msk)  | (7 << GPIO_AFRL_AFSEL7_Pos);

    //GPIOB->AFR[0] |= (7<<GPIO_AFRL_AFSEL6_Pos) | (7<<GPIO_AFRL_AFSEL7_Pos);
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    //Pour faire le reset du port série
    RCC->APB2RSTR |=  RCC_APB2RSTR_USART1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

    //Pour configurer l'oversampling
    //USART1->CR1= (0<<15);//C'est 0 parce que en bit 15 en 0 l'oversampling est à 16
    USART1->CR1 = 0;
    USART1->CR2 = 0;

    //Pour la vitesse du port série à 115200
    USART1->BRR = (int)80000000/baudrate; // modifié pour le IRQ+UART+LED


    //Pour activer l'USART1

    USART1->CR1 |= USART_CR1_UE; //Transmetteur
    //USART1-> CR1 = (1<<2); //Récepteur
    USART1-> CR1 |= USART_CR1_RE; //Récepteur

    //USART1->CR1= (1<<3); //Transmetteur
    USART1->CR1 |= USART_CR1_TE; //Transmetteur

    //Si il reçoit une trame, active rxneie pour envoyer l'interruption
    USART1->CR1 |= USART_CR1_RXNEIE;

    NVIC_EnableIRQ(USART1_IRQn);
}

void uart_putchar(uint8_t c){
    //While le TXE=0, faire no operation
    while (!(USART1->ISR & USART_ISR_TXE_Msk)){
        asm volatile("nop");
    }
    USART1->TDR=c;//si TXE=1, envoyer la valeur c
}

uint8_t uart_getchar(){
    //While RXNE=0, faire no operation
    while (!(USART1->ISR & USART_ISR_RXNE_Msk)){
        asm volatile("nop");
    }
    return USART1->RDR; //si RXNE=1,il doit returner la valeur
}

void uart_puts(const char *s){
    int i = 0 ;
    while(s[i] != '\0'){ // si c'est pas la fin de char
        uart_putchar(s[i]);//envoyer la valeur
        i++ ;
    }
}

void uart_gets(char *s, size_t size){
    int i=0;
    while(s[i] < size){//si c'est moin que la taille de char
        uart_getchar();//returner la valeur
        i++;
    }
}

void USART1_IRQHandler(void){
    uint8_t byte = uart_getchar();
    if((byte==0xff) | (cont==192)){
        cont=0;
    }else{
        if((cont%3) == 0){
            image_matrix[(uint8_t)(cont/3)].r = byte;
        }
        if((cont%3)== 1){
            image_matrix[(uint8_t)(cont/3)].g = byte;
        }
        if((cont%3) == 2){
            image_matrix[(uint8_t)(cont/3)].b = byte;
        }
        //uart_putchar(byte);
        cont++;
    }
}
