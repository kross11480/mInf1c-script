#include <l298n.h>
#include "movement.h"

#include <libstefi/util.h>

motor_t left_motor;
motor_t right_motor;

int speed_high = 100;
int speed_low = 30;
int speed_turn_high = 80;
int speed_turn_low = 20;
int speed_yaw = 60;
int speed_forward = 60;
int speed_back = 60;
int speed_impulse = 60;
float left_motor_factor = 0.97;
float right_motor_factor = 1;
int turn_duration = 480;

void movement_init() {
    l298n_motor_init(&right_motor, A8, A11);
    l298n_motor_init(&left_motor, B5, B4);

    //A0 to right wheel speed PWM and A1 to left wheel
    gpio_set_mode(A0, MODER_AF);
    gpio_set_alternate_function(A0, AF1);
    gpio_set_mode(A1, MODER_AF);
    gpio_set_alternate_function(A1, AF1);

    timer_init(TIMER2);
    timer_set_period(TIMER2, 16, 255); //PWM Freq=16 MhZ/(16*256) = 4 KHZ

    timer_set_mode_pwm(TIMER2, TIMER_CHANNEL1);
    timer_cc_enable(TIMER2, TIMER_CHANNEL1, false);
    timer_set_compare(TIMER2, TIMER_CHANNEL1, 0);

    timer_set_mode_pwm(TIMER2, TIMER_CHANNEL2);
    timer_cc_enable(TIMER2, TIMER_CHANNEL2, false);
    timer_set_compare(TIMER2, TIMER_CHANNEL2, 0);

    timer_start(TIMER2);
}

static void set_speed(int v_left, int v_right) {
    timer_set_compare(TIMER2, TIMER_CHANNEL1, 255 - right_motor_factor* 2.55 * v_right);
    timer_set_compare(TIMER2, TIMER_CHANNEL2, 255 - left_motor_factor * 2.55 * v_left);
}

void move_forward() {
    // Apply impulse to both motors to overcome static friction
    set_speed(speed_impulse, speed_impulse);
    // Set forward motion
    l298n_motor_drive(&left_motor, MOTOR_FORWARD);
    l298n_motor_drive(&right_motor, MOTOR_FORWARD);
    soft_delay_ms(10);

    set_speed(speed_forward, speed_forward);
    l298n_motor_drive(&left_motor, MOTOR_FORWARD);
    l298n_motor_drive(&right_motor, MOTOR_FORWARD);
}

void move_backward() {
    // Apply impulse to both motors
    set_speed(speed_impulse, speed_impulse);
    //set reverse motion
    l298n_motor_drive(&left_motor, MOTOR_REVERSE);
    l298n_motor_drive(&right_motor, MOTOR_REVERSE);
    soft_delay_ms(10);
    set_speed(speed_back, speed_back);
    l298n_motor_drive(&left_motor, MOTOR_REVERSE);
    l298n_motor_drive(&right_motor, MOTOR_REVERSE);
}

void move_stop() {
    // Set brake motion
    l298n_motor_drive(&left_motor, MOTOR_BRAKE);
    l298n_motor_drive(&right_motor, MOTOR_BRAKE);
}

void turn_right() {
    set_speed(speed_impulse, speed_impulse);
    l298n_motor_drive(&left_motor, MOTOR_FORWARD);
    l298n_motor_drive(&right_motor, MOTOR_FORWARD);
    soft_delay_ms(10);

    set_speed(speed_high, speed_low);
    l298n_motor_drive(&left_motor, MOTOR_FORWARD);
    l298n_motor_drive(&right_motor, MOTOR_FORWARD);
}

void turn_left() {
    set_speed(speed_impulse, speed_impulse);
    l298n_motor_drive(&left_motor, MOTOR_FORWARD);
    l298n_motor_drive(&right_motor, MOTOR_FORWARD);
    soft_delay_ms(10);

    set_speed(speed_low, speed_high);
    l298n_motor_drive(&left_motor, MOTOR_FORWARD);
    l298n_motor_drive(&right_motor, MOTOR_FORWARD);
}

void yaw_right() {
    // Apply impulse to both motors
    set_speed(speed_impulse, speed_impulse);

    l298n_motor_drive(&left_motor, MOTOR_FORWARD);
    l298n_motor_drive(&right_motor, MOTOR_REVERSE);
    soft_delay_ms(50);

    set_speed(speed_yaw, speed_yaw);
    l298n_motor_drive(&left_motor, MOTOR_FORWARD);
    l298n_motor_drive(&right_motor, MOTOR_REVERSE);
}

void yaw_left() {
    // Apply impulse to both motors
    set_speed(speed_impulse, speed_impulse);

    l298n_motor_drive(&left_motor, MOTOR_REVERSE);
    l298n_motor_drive(&right_motor, MOTOR_FORWARD);
    soft_delay_ms(50);
    set_speed(speed_yaw, speed_yaw);
    l298n_motor_drive(&left_motor, MOTOR_REVERSE);
    l298n_motor_drive(&right_motor, MOTOR_FORWARD);
}