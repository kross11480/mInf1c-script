#pragma once
#include "pin.h"

typedef struct {
    pin_id_t echo_pin;
    pin_id_t trig_pin;
    tim_id_t tim;
    timer_channel_t channel;
} ultrasonic_config_t;

void ultrasonic_init(pin_id_t echo_pin, pin_id_t trig_pin, tim_id_t capture_timer, timer_channel_t capture_channel);
int ultrasonic_measure();