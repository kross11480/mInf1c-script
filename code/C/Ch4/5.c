//Task: Implement Button API (button.h)
//      * define stefi buttons
//      * debouncing with strategy pattern,
//      * initially soft blocking delay and no timer, later with timer
//      * Implementation in button.c (start debouncing timer in exti handler.)
#include <stdbool.h>
#include <stdint.h>
#include "util.h"
#include "gpio.h"
#include "peripheral.h"
#include "button.h"
#include "timer.h"

#define TIMER2_ID TIM4
#define TIMER2_IT INTERRUPT_SOURCE_TIM4

void button_callback()
{
    timer_start(TIMER2_ID);
}

void debounced_toggle() {
    timer_stop(TIMER2_ID); //reset timer
    bool debounced_state_is_pressed = button_is_pressed(BUTTON_S0);
    if(debounced_state_is_pressed) {
        gpio_toggle(A0);
    }
}

void main() {
    peripheral_gpioA_enable();
    gpio_set_mode(A0, MODER_OUTPUT);

    button_init(BUTTON_S0);
    button_interrupt_init(BUTTON_S0, button_callback);

    //initialize debounce timer to 10ms
    timer_init_periodic(TIMER2_ID, TIMER2_IT, debounced_toggle, 16000, 10);
    timer_enable_interrupt(TIMER2_ID);
    interrupts_enable_source(TIMER2_IT);

    while (1) {
    }
}