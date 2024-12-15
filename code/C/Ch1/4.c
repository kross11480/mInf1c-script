#include<stdint.h>
#include<stm32g431xx.h>

void setup(){
    //initialize gpio
    RCC->AHB2ENR |= 0x1; //Enable Clock for GPIOA
    GPIOA->MODER &= ~(0x30);
    GPIOA->MODER |= (0x10);
}

void delay(uint32_t count) {
    while (count--)
        asm("NOP");
}

int main(void){
    setup();

    while(1){
        GPIOA->ODR ^= 0x4;
        delay(500000);
    }
}
