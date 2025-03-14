#include "timer.h"
#include "debounce.h"
#include "button.h"

#define DEB_TIMER_ID TIM4
#define DEB_TIMER_IT INTERRUPT_SOURCE_TIM4

static stefi_button_t button_to_debounce;
static debounce_callback_t debounce_callback;

void debounce_init(){
    //initialize debounce timer to 40ms
    timer_init_periodic(DEB_TIMER_ID, DEB_TIMER_IT, debounced_reaction, 16000, 40);
}

void debounce_start(stefi_button_t button, debounce_callback_t callback) {
    button_to_debounce = button;
    debounce_callback = callback;
    timer_start(DEB_TIMER_ID);
}

void debounced_reaction() {
    timer_reset(DEB_TIMER_ID);
    if(button_is_pressed(button_to_debounce)) {
        debounce_callback();
    }
}

