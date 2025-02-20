#ifndef LED_H
#define LED_H

#include "gpio.h"
#include  "stdint.h"

typedef enum {
    LED_RED,
    LED_YELLOW,
    LED_GREEN,
    LED_BLUE,
} stefi_led_t;

typedef struct {
    gpio_id_t portpin;
    sig_t off_state;
} LEDConfig;

//Functions
void led_init(stefi_led_t id);
void led_on(stefi_led_t id);
void led_off(stefi_led_t id);
void led_toggle(stefi_led_t);
void led_set(uint8_t mask);

#endif