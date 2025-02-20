#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

#include "gpio.h"
#include "interrupts.h"

typedef enum {
    BUTTON_S0,
    BUTTON_S1,
    BUTTON_S2,
    BUTTON_S3
} stefi_button_t;

typedef enum {
    NO_DEBOUNCE,
    SOFTWARE_DEBOUNCE,
} DebounceStrategy_t;

typedef struct {
    nvic_source_t irq;
    DebounceStrategy_t debounce;
    void (*debounce_fn)();
    void (*callback_fn)();
} stefi_buttons_config_t;

//Button Confguration
typedef struct {
    gpio_id_t portpin;
    pupdr_t pull;
} ButtonConfig;

//Functions
void button_init(stefi_button_t id);
void button_interrupt_init(stefi_button_t id, callbackfn_typeDef fn);
bool button_is_pressed(stefi_button_t id);
#endif // BUTTON_H
