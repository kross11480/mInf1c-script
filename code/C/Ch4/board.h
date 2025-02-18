#include "gpio.h"
#include "button.h"

ButtonConfig buttons[NUM_BUTTONS] = {
    [BUTTON_S0] = {B0, PULL_UP},
    [BUTTON_S1] = {B4, PULL_UP},
    [BUTTON_S2] = {B5, PULL_UP},
    [BUTTON_S3] = {B7, PULL_UP}
};
