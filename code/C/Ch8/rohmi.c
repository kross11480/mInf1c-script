// Task: Empty Template: turning on LED1 on libstefi
#include <libstefi/uart.h>
#include <libstefi/util.h>

#include "movement.h"
#include "navigation.h"
#include "tracker.h"
#include "ultrasonic.h"

void main(){
    uart_configure();
    ultrasonic_init(B7, B0, TIMER3, TIMER_CHANNEL4);
    movement_init();
    tracker_init();
    while(1) {
        //move_forward();
        //obstacle_avoidance();
        line_follower();
        //yaw_right();
    }
}

