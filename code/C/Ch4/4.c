#include "gpio.h"
#include "peripheral.h"
#include "interrupts.h"

#define BUTTON_ID B5
#define BUTTON_IT INTERRUPT_SOURCE_EXTI5_9

void button_callback()
{
    gpio_toggle(A0);
}

void main() {
    const int buttons[3] = {[0] = 1, [1] = 2, [2] = 3};
    peripheral_gpioA_enable();
    peripheral_gpioB_enable();

    gpio_set_mode(BUTTON_ID, MODER_INPUT);
    gpio_set_pupd(BUTTON_ID, PULL_UP);
    gpio_set_mode(A0, MODER_OUTPUT);

    gpio_enable_interrupt(BUTTON_ID, FALLING_EDGE);
    gpio_interrupt_register_handler(BUTTON_ID, button_callback);
    interrupts_enable_source(BUTTON_IT);
    while (1) {
    }
}