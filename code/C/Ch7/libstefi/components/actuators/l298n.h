#pragma once
#include "libstefi/gpio.h"
#include "pin.h"

typedef enum {
    MOTOR_NOPOWER,
    MOTOR_FORWARD,
    MOTOR_REVERSE,
    MOTOR_BRAKE,
} motor_action_t;

typedef struct {
    pin_id_t in1;
    pin_id_t in2;
} motor_t;

//Functions
void l298n_motor_init(motor_t *m, pin_id_t in1, pin_id_t in2);
void l298n_motor_drive(motor_t *m, motor_action_t action);