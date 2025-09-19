// Task: Empty Template: turning on LED1 on libstefi
#include <libstefi/util.h>
#include "libstefi/gpio.h"
#include "libstefi/peripheral.h"

#include "l298n.h"

motor_t left_motor;
motor_t right_motor;

void main(){

    l298n_motor_init(&left_motor, A8, A11);
    l298n_motor_init(&right_motor, B5, B4);

    while(1) {
        l298n_motor_drive(&left_motor, MOTOR_FORWARD);
        l298n_motor_drive(&right_motor, MOTOR_REVERSE);
        soft_delay_ms(10);
        l298n_motor_drive(&left_motor, MOTOR_BRAKE);
        l298n_motor_drive(&right_motor, MOTOR_BRAKE);
        soft_delay_ms(100);
    }
}