// Task: Empty Template: turning on LED1 on libstefi
#include "libstefi/gpio.h"
#include "libstefi/peripheral.h"
#include "libstefi/util.h"



void main(){
    gpio_pin_t led = gpio_init(C4);

    peripheral_gpio_enable(PERIPHERAL_ID_GPIOC);
    gpio_set_mode(&led, MODER_OUTPUT); // LED1 on Port C pin 5 on STefi
    while (1) {
        gpio_toggle(&led);
        soft_delay_ms(500);
    }
}