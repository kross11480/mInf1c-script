#pragma once
#include "libstefi/gpio.h"
#include "libstefi/timer.h"

typedef enum {
    LED0_RED = 0,
    LED1_YELLOW,
    LED2_GREEN,
    LED3_BLUE,
    NUM_LEDS
} stefi_led_t;

typedef enum {
    BUTTON_S0 = 0,
    BUTTON_S1,
    BUTTON_S2,
    BUTTON_S3,
    NUM_BUTTONS
} stefi_button_t;

typedef struct {
    gpio_id_t portpin;
    sig_t off_state;
    tim_id_t timer_id;
    uint32_t channel;
    afr_t af_mode;
}  led_config_t;

//Button Confguration
typedef struct {
    gpio_id_t portpin;
    pupdr_t pull;
} button_config_t;

extern led_config_t leds[NUM_LEDS];
extern button_config_t buttons[NUM_BUTTONS];