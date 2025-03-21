// Task: Empty Template: turning on LED1 on libstefi
#include "libstefi/gpio.h"
#include "libstefi/peripheral.h"
#include "libstefi/util.h"

void main(){
    peripheral_gpioC_enable();
    gpio_set_mode(C5, MODER_OUTPUT);
    gpio_write(C5, LOW);
    while (1) {
        gpio_toggle(C5);
        soft_delay_ms(250);
    }
}