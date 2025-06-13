#pragma once

#include "board.h"
#include  "stdint.h"

//Functions
void led_init(stefi_led_t id);
void led_on(stefi_led_t id);
void led_off(stefi_led_t id);
void led_toggle(stefi_led_t);
void led_set(uint8_t mask);