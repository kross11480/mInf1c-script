#include <stdint.h>

#include "gpio.h"
#include "button.h"
#include "peripheral.h"
#include "board.h"


void button_init(stefi_button_t id) {
    peripheral_gpioB_enable();
    gpio_set_mode(buttons[id].portpin, MODER_INPUT);
    gpio_set_pupd(buttons[id].portpin, PULL_UP);
}

nvic_source_t get_exti_irq(stefi_button_t id) {
    uint16_t pin = buttons[id].portpin & 0xFF;
    switch(pin) {
        case 0: return INTERRUPT_SOURCE_EXTI0;
        case 4: return INTERRUPT_SOURCE_EXTI4;
        case 5:;
        case 7: return  INTERRUPT_SOURCE_EXTI5_9;
        default: return -1;
    }
}

void button_interrupt_init(stefi_button_t id, callbackfn_typeDef fn) {
    buttons[id].it.irq = get_exti_irq(id);
    buttons[id].it.callback_fn = fn;
    gpio_enable_interrupt(buttons[id].portpin, FALLING_EDGE);
    gpio_interrupt_register_handler(buttons[id].portpin, fn);
    interrupts_enable_source(buttons[id].it.irq);
}