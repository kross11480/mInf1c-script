#include <libstefi/peripheral.h>

#include "libstefi/gpio.h"

#include "libstefi/interrupts.h"

#define BUTTON_ID B7
#define LED_ID A0

void button_callback()
{
    gpio_toggle(LED_ID);
}

void main() {
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOC);
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOB);
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOA);

    gpio_set_mode(BUTTON_ID, MODER_INPUT);
    gpio_set_pupd(BUTTON_ID, PULL_UP);
    gpio_set_mode(LED_ID, MODER_OUTPUT);

    gpio_enable_interrupt(BUTTON_ID, FALLING_EDGE);
    gpio_interrupt_register_handler(BUTTON_ID, button_callback);

    while (1) {
    }
}