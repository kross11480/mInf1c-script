#include "libstefi/timer.h"
#include "debounce.h"
#include "button.h"


static stefi_button_t button_to_debounce;
static debounce_callback_t debounce_callback;

static void debounced_reaction() {
    timer_stop(DEB_TIMER_ID);
    if(button_is_pressed(button_to_debounce)) {
        debounce_callback();
    }
}

void debounce_init(){
    static bool initialized = false;
    if (initialized) return;
    initialized = true;

    //initialize debounce timer to 40ms
    timer_init(DEB_TIMER_ID);
    timer_set_period(DEB_TIMER_ID, DEB_PSC, DEB_PERIOD);
    timer_interrupt_register_handler(DEB_TIMER_ID, debounced_reaction);
    timer_enable_interrupt(DEB_TIMER_ID);
}

void debounce_start(stefi_button_t button, debounce_callback_t callback) {
    button_to_debounce = button;
    debounce_callback = callback;
    timer_start(DEB_TIMER_ID);
}