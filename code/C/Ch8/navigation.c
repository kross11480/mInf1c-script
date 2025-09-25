#include "movement.h"
#include "ultrasonic.h"
#include "navigation.h"

#include <stdio.h>
#include <libstefi/util.h>

#define SAFE_DISTANCE 15   // cm: minimum clearance to move forward
#define SCAN_DELAY    200  // ms: delay while turning to scan
#define BACKOFF_DELAY 30  // ms: backup time

void obstacle_avoidance() {
    int distance = ultrasonic_measure();

    if (distance > SAFE_DISTANCE) {
        // Path is clear
        move_forward();
        printf("FORWARD \r\n");
        soft_delay_ms(200);
        return;
    }

    // Obstacle detected
    move_stop();
    soft_delay_ms(200);

    // Back off a little to avoid getting too close
    move_backward();
    soft_delay_ms(BACKOFF_DELAY);
    move_stop();
    soft_delay_ms(200);

    // Scan right
    yaw_right();
    soft_delay_ms(SCAN_DELAY);
    move_stop();
    int dist_right = ultrasonic_measure();

    // Return to center
    yaw_left();
    soft_delay_ms(SCAN_DELAY);
    move_stop();

    // Scan left
    yaw_left();
    soft_delay_ms(SCAN_DELAY);
    move_stop();
    int dist_left = ultrasonic_measure();

    // Return to center
    yaw_right();
    soft_delay_ms(SCAN_DELAY);
    move_stop();

    // Decide which way is better
    if (dist_right > dist_left && dist_right > SAFE_DISTANCE) {
        yaw_right();
        soft_delay_ms(SCAN_DELAY);
        move_forward();
        soft_delay_ms(200);
        printf("RIGHT \r\n");
    } else if (dist_left > SAFE_DISTANCE) {
        yaw_left();
        soft_delay_ms(SCAN_DELAY);
        move_forward();
        soft_delay_ms(200);
        printf("LEFT \r\n");
    } else {
        // Both blocked, turn around
        yaw_left();
        soft_delay_ms(2 * SCAN_DELAY);  // ~180° turn
        move_forward();
        soft_delay_ms(200);
        printf("TURN AROUND \r\n");
    }
}
