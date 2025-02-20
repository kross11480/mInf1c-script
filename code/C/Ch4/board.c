#include "board.h"

ButtonConfig buttons[NUM_BUTTONS] = {
    [BUTTON_S0] = {B0, PULL_UP},
    [BUTTON_S1] = {B4, PULL_UP},
    [BUTTON_S2] = {B5, PULL_UP},
    [BUTTON_S3] = {B7, PULL_UP}
};

LEDConfig leds[NUM_LEDS] = {
    [LED_RED] = {A0, HIGH},
    [LED_YELLOW] = {A1, HIGH},
    [LED_GREEN] = {A2, HIGH},
    [LED_BLUE] = {A3, HIGH},
};