#include "gpio.h"
#include "peripheral.h"


void main() {
    peripheral_gpioA_enable();
    peripheral_gpioB_enable();

    gpio_set_mode(B0, MODER_INPUT);
    gpio_set_pupd(B0, PULL_UP);
    gpio_set_mode(A0, MODER_OUTPUT);

    gpio_enable_interrupt(B0, FALLING_EDGE);

}