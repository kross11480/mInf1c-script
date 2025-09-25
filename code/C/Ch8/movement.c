#include <l298n.h>
#include "movement.h"

motor_t left_motor;
motor_t right_motor;

void movement_init() {
    l298n_motor_init(&left_motor, A8, A11);
    l298n_motor_init(&right_motor, B5, B4);
}

void move_forward() {
    // Apply impulse to both motors

    // Set forward motion
    l298n_motor_drive(&left_motor, MOTOR_FORWARD);
    l298n_motor_drive(&right_motor, MOTOR_FORWARD);
}

void move_backward() {
    // Apply impulse to both motors

    // Set forward motion
    l298n_motor_drive(&left_motor, MOTOR_REVERSE);
    l298n_motor_drive(&right_motor, MOTOR_REVERSE);
}

void move_stop() {
    // Apply impulse to both motors

    // Set forward motion
    l298n_motor_drive(&left_motor, MOTOR_BRAKE);
    l298n_motor_drive(&right_motor, MOTOR_BRAKE);
}

void yaw_right() {
    l298n_motor_drive(&left_motor, MOTOR_FORWARD);
    l298n_motor_drive(&right_motor, MOTOR_REVERSE);
}

void yaw_left() {
    l298n_motor_drive(&left_motor, MOTOR_REVERSE);
    l298n_motor_drive(&right_motor, MOTOR_FORWARD);
}