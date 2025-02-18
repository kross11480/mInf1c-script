//Task: Implement Button API (button.h)
//      * define stefi buttons
//      * debouncing with strategy pattern,
//      * initially soft blocking delay and no timer, later with timer
//      * Implementation in button.c
#include <stdbool.h>
#include <stdint.h>

#include "gpio.h"
#include "peripheral.h"
#include "button.h"

void button_callback()
{
    gpio_toggle(A0);
}

void main() {
    peripheral_gpioA_enable();
    gpio_set_mode(A0, MODER_OUTPUT);

    button_init(BUTTON_S0);
    button_interrupt_init(BUTTON_S0, button_callback);

    while (1) {

    }
}