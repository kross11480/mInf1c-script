// Task: Empty Template: turning on LED1 on libstefi
#include "libstefi/gpio.h"
#include "libstefi/peripheral.h"
#include "libstefi/util.h"

void main(){
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOC);
    gpio_set_mode(C5, MODER_OUTPUT);
    while (1) {
        gpio_toggle(C5);
        soft_delay_ms(250);
    }
}