#include<stdint.h>
#include<stm32g431xx.h>

/* Task: Rewrite the code as event/action loop
    led: 0,3 -> PA0 ..3
    button: S1: PB0, S2: PB4, S3: PB5, S4: PB4
*/


typedef enum {
    B_PRESSED,
    B_RELEASED
} event_t;

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

void led_toggle(){
    GPIOA->ODR ^= 0x4;
}

void led_off(){
    GPIOA->ODR |= 0X4;
}

void loop() {
    event_t event;
    event = (GPIOB->IDR & (0x1)); //1 is button released
    if(event == B_RELEASED){
        led_off();
    }
    else{
        led_toggle();
    }
    delay(500000);
}

void loop_switch(){
    event_t event;
    event = (GPIOB->IDR & (0x1)); //1 is button released

    switch (event){
    case B_RELEASED:
        led_off();
        break;
    case B_PRESSED:
        led_toggle();
        break;
    }

    delay(500000);
}

int main(void){

    setup();
    while(1){
        loop_switch();
    }
}
