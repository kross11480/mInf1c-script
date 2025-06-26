#include "board.h"


button_config_t buttons[NUM_BUTTONS] = {
    [BUTTON_S0] = {B0, PULL_UP},
    [BUTTON_S1] = {B1, PULL_UP},
    [BUTTON_S2] = {B2, PULL_UP},
    [BUTTON_S3] = {B3, PULL_UP}
};

led_config_t leds[NUM_LEDS] = {
    [LED0_RED] = {C4, HIGH},
    [LED1_YELLOW] = {C5, HIGH},
    [LED2_GREEN] = {C6, HIGH, TIMER3, 1, AF2},
    [LED3_BLUE] = {C7, HIGH, TIMER3, 2, AF2},
};


