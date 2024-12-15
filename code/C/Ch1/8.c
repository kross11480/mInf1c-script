#include<stdint.h>
#include<stm32g431xx.h>

/* Task: Polling
    led: 0,3 -> PA0 ..3
    button: S1: PB0, S2: PB4, S3: PB5, S4: PB4
*/

void setup(){
    //initialize gpio
    RCC->AHB2ENR |= 0x1 | 0X2; //Enable Clock for GPIOA AND GPIOB

    GPIOA->MODER &= ~(0x30);
    GPIOA->MODER |= (0x10);

    GPIOB->MODER &= ~(0x3);
    GPIOB->PUPDR &= ~(0x3);
    GPIOB->PUPDR |= (0x1);
}

void delay(uint32_t count) {
    while (count--)
        asm("NOP");
}

int main(void){
    setup();

    while(1){
        if( (GPIOB->IDR & (0x1)) == 0x1){
            GPIOA->ODR ^= 0x4;
        }
        else{
            GPIOA->ODR |= 0X4;
        }
        delay(500000);
    }
}
