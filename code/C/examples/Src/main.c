#include "stdbool.h"
#include "inttypes.h"

#define LED_POS 6
#define DELAY 500

volatile uint32_t *const rcc_clock_enable = (uint32_t *) 0x4002104C;

struct gpio {
    volatile uint32_t MODER;    // GPIO port mode register
    volatile uint32_t OTYPER;   // GPIO port output type register
    volatile uint32_t OSPEEDR;  // GPIO port output speed register
    volatile uint32_t PUPDR;    // GPIO port pull-up/pull-down register
    volatile uint32_t IDR;      // GPIO port input data register
    volatile uint32_t ODR;      // GPIO port output data register
    volatile uint32_t BSRR;     // GPIO port bit set/reset register
    volatile uint32_t LCKR;     // GPIO port configuration lock register
    volatile uint32_t AFR[2];   // GPIO alternate function low and high register
};

#define gpioC ((struct gpio *)0x48000800)

void set_bit(volatile uint32_t *const reg, int pos){
    *reg |= (1U << pos);
}

void clear_bit(volatile uint32_t *const reg, int pos){
    *reg &= ~(1U << pos);
}

void toggle_bit(volatile uint32_t *const reg, int pos){
    *reg ^= (1U << pos);
}

void initialize(){
    /* initialize clock */
    set_bit(rcc_clock_enable, 2);
    set_bit(rcc_clock_enable, 1);
    /* initialize blue led on port C7*/
    gpioC->MODER &= ~(1 << 2*LED_POS+1);
    gpioC->ODR |= (1 << LED_POS);
}

void sleep(uint32_t ms){
    for(int i = 0; i < 400; i++)
        for(int j = 0; j < ms; j++){
            asm("nop");
        }
}

void toggle_led(uint32_t pos){
    gpioC->ODR ^= (1 << LED_POS);
    sleep(DELAY);
}

int main(void){
    bool state = false;
    initialize();
    while(1) {

    }
    return 0;
}



