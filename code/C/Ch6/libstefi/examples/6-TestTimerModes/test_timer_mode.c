#include <libstefi/board.h>
#include <libstefi/rng.h>
#include <libstefi/systick.h>
#include <libstefi/timer.h>
#include <libstefi/uart.h>

#include "stdio.h"
#include "led.h"
#include "button.h"

#define LED LED2_GREEN


void setup() {
    led_init(LED, PWM);

    systick_init();
    systick_start();
}

void main() {
    //initialize uart
    uart_configure();
    printf("\r\n Start PWM-based LED fading \r\n");

    setup();

    while(1) {
        // Fade-in
        for (int duty = 0; duty <255; duty++) {
            led_set_brightness(LED, duty);
            systick_delay_ms(8);
        }

        // Fade-out
        for (int duty = 256; duty > 0; duty--) {
            led_set_brightness(LED, duty);
            systick_delay_ms(8);
        }
    }
}