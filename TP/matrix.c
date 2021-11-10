#define STM32L475xx //c'est où se trouve le typedef
//#include "stm32l4xx.h"  //on doit incluire le fichier pour l'utiliser
#include "matrix.h"
#include "memory.h"

void pulse_LAT(){ //pulse négatif --> 1 0 1
    LAT(1);
    asm volatile("nop");
    asm volatile("nop");
    LAT(0);
    asm volatile("nop");
    asm volatile("nop");
    LAT(1);
}


//pulse positif --> 0 1 0
void pulse_SCK(){
    SCK(0);
    for (int i=0; i<3; i++){
        asm volatile("nop");
    }

    SCK(1);
    for (int i=0; i<3; i++){
        asm volatile("nop");
    }

    SCK(0);
    for (int i=0; i<3; i++){
        asm volatile("nop");
    }

}

//Envoyer 8 bits consécutifs au bank spécifié par le paramètre bank (0 ou 1)
void send_byte(uint8_t val, int bank){
    SB(bank);
    for (int i=0; i < 8; i++){
        SDA((val>>(7-i)) & 1);
        pulse_SCK();
    }
}


void init_bank0(){

    //144/8=18, chaque boucle il envoie 8 bits a bank0, 144 bits en total
    for (int i=0; i<18; i++){
        send_byte(255,0);
    }
    pulse_LAT();
}

void matrix_init(){

    //Mettre en marche les horloges de port A, B et C
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN); //Port A
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN); //Port B
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN); //Port C


    //Toutes les broches en mode GPIO Output ---> (01)
    //Pour port A, on a besoin de 4,15,2,7,6,5,3
    GPIOA->MODER = (GPIOA -> MODER & ~GPIO_MODER_MODE4_1) |(GPIO_MODER_MODE4_0);
    GPIOA->MODER = (GPIOA -> MODER & ~GPIO_MODER_MODE15_1) |(GPIO_MODER_MODE15_0);
    GPIOA->MODER = (GPIOA -> MODER & ~GPIO_MODER_MODE2_1) |(GPIO_MODER_MODE2_0);
    GPIOA->MODER = (GPIOA -> MODER & ~GPIO_MODER_MODE7_1) |(GPIO_MODER_MODE7_0);
    GPIOA->MODER = (GPIOA -> MODER & ~GPIO_MODER_MODE6_1) |(GPIO_MODER_MODE6_0);
    GPIOA->MODER = (GPIOA -> MODER & ~GPIO_MODER_MODE5_1) |(GPIO_MODER_MODE5_0);
    GPIOA->MODER = (GPIOA -> MODER & ~GPIO_MODER_MODE3_1) |(GPIO_MODER_MODE3_0);

    //Pourt port b, on a besoin de 1,2,0
    GPIOB->MODER = (GPIOB -> MODER & ~GPIO_MODER_MODE1_1) |(GPIO_MODER_MODE1_0);
    GPIOB->MODER = (GPIOB -> MODER & ~GPIO_MODER_MODE2_1) |(GPIO_MODER_MODE2_0);
    GPIOB->MODER = (GPIOB -> MODER & ~GPIO_MODER_MODE0_1) |(GPIO_MODER_MODE0_0);

    //Pour port C, on a besoind de 5,4,3
    GPIOC->MODER = (GPIOC -> MODER & ~GPIO_MODER_MODE5_1) |(GPIO_MODER_MODE5_0);
    GPIOC->MODER = (GPIOC -> MODER & ~GPIO_MODER_MODE4_1) |(GPIO_MODER_MODE4_0);
    GPIOC->MODER = (GPIOC -> MODER & ~GPIO_MODER_MODE3_1) |(GPIO_MODER_MODE3_0);

    //Toutes les broches en trés haute vitesse --> (11)

    GPIOA->OSPEEDR = (GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_1) | (GPIO_OSPEEDR_OSPEED4_0);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED15_1) | (GPIO_OSPEEDR_OSPEED15_0);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_1) | (GPIO_OSPEEDR_OSPEED2_0);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED7_1) | (GPIO_OSPEEDR_OSPEED7_0);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_1) | (GPIO_OSPEEDR_OSPEED6_0);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_1) | (GPIO_OSPEEDR_OSPEED5_0);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_1) | (GPIO_OSPEEDR_OSPEED3_0);

    GPIOB->OSPEEDR = (GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_1) | (GPIO_OSPEEDR_OSPEED1_0);
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_1) | (GPIO_OSPEEDR_OSPEED2_0);
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_1) | (GPIO_OSPEEDR_OSPEED0_0);

    GPIOC->OSPEEDR = (GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_1) | (GPIO_OSPEEDR_OSPEED5_0);
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_1) | (GPIO_OSPEEDR_OSPEED4_0);
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_1) | (GPIO_OSPEEDR_OSPEED3_0);

    //Positionner ces sorties à une valeur initiale acceptable
    RST(0);
    LAT(1);
    SB(1);
    SCK(0);
    SDA(0);

    //éteint toutes les lignes
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);

    //Attend 100ms et RST(1)

    for (int i=0; i<100; i++){
        asm volatile("nop");
    }
    RST(1); //état haut

    //appel la fonction pour mettre tous les bits de bank0 à 1
    init_bank0();

    //prover le led matrix avec un melange entre rouge et blue
    memcpy(image_matrix, &_binary_image_raw_start, 192);
}

void deactivate_rows(){
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

// Activates an asked row
void activate_row(int row){
    switch (row) {
        case 0:
            ROW0(1);
            break;
        case 1:
            ROW1(1);
            break;
        case 2:
            ROW2(1);
            break;
        case 3:
            ROW3(1);
            break;
        case 4:
            ROW4(1);
            break;
        case 5:
            ROW5(1);
            break;
        case 6:
            ROW6(1);
            break;
        case 7:
            ROW7(1);
            break;
    }
}



void mat_set_row(int row, const rgb_color *val){
    for (int i=0; i<=7; i++){
        //dans le bon ordre B G R
        send_byte(val[7-i].b,1);
        send_byte(val[7-i].g,1);
        send_byte(val[7-i].r,1);
    }

    deactivate_rows();

    for (int i=0; i<3; i++){
        asm volatile("nop");
    }

    pulse_LAT();
    activate_row(row);

}

void test_pixels(){
    for (uint32_t i=0; i<8; i++){
        mat_set_row(i, image_matrix + i * 8);
    }
}

