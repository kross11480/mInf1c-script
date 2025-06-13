#include "libstefi/gpio.h"
#include "button.h"
#include "libstefi/peripheral.h"
#include "board.h"

void button_init(stefi_button_t id) {
    peripheral_gpio_enable(gpio_get_port(buttons[id].portpin));
    gpio_set_mode(buttons[id].portpin, MODER_INPUT);
    gpio_set_pupd(buttons[id].portpin, PULL_UP);
}

void button_interrupt_init(stefi_button_t id, callbackfn_typeDef fn) {
    //Falling Edge Hard-Coded
    gpio_enable_interrupt(buttons[id].portpin, FALLING_EDGE);
    gpio_interrupt_register_handler(buttons[id].portpin, fn);
}

bool button_is_pressed(stefi_button_t id) {
    //currently only for pull down
    sig_t button_state = gpio_read(buttons[id].portpin);
    return button_state ? false : true;
}