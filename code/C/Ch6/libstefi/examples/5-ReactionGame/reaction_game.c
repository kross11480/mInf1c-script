#include <libstefi/rng.h>
#include <libstefi/systick.h>
#include <libstefi/timer.h>
#include <libstefi/uart.h>

#include "stdio.h"
#include "led.h"
#include "button.h"
#include "debounce.h"
#include "ssd1306.h"

#define TIMER_ID TIMER3


void s0_action() {
    //wait a random timer
    led_off(LED0_RED);
    timer_start(TIMER_ID);
    //random time between 0.5 and 1s
    volatile uint32_t rnd_time = 500 + rng_get_rand()/(0x1 << 20);
    while(timer_getcount(TIMER_ID) <= rnd_time);
    timer_stop(TIMER_ID);
    // start game
    led_on(LED0_RED);
    // start reaction timer
    timer_start(TIMER_ID);
}

void s1_action() {
    char buffer[10];
    led_off(LED0_RED);
    ssd1306_clear_screen();
    sprintf(buffer, "TIME: %4d", timer_getcount(TIMER_ID));
    //printf("Time: %lu \r\n", timer_getcount(TIMER_ID));
    ssd1306_putstring( 5, 0, buffer);
    ssd1306_update_screen();
    timer_stop(TIMER_ID);
}

void s0_callback() {
    debounce_start(BUTTON_S0, s0_action);
}


void s1_callback() {
    debounce_start(BUTTON_S1, s1_action);
}

void timer_expires() {
    printf("Slow Finger \r\n");
    timer_stop(TIMER_ID);
}

void setup() {
    //initialize button
    rng_init();
    button_init(BUTTON_S0);
    button_interrupt_init(BUTTON_S0, s0_callback);

    button_init(BUTTON_S1);
    button_interrupt_init(BUTTON_S1, s1_callback);
    //initialize led
    led_init(LED0_RED);
    //initialize reaction timer
    timer_init(TIMER_ID);
    timer_set_period(TIMER_ID, 4000, 5000);
    timer_interrupt_register_handler(TIMER_ID, timer_expires);
    timer_enable_interrupt(TIMER_ID);

    systick_init();
    systick_start();
    ssd1306_init();
    systick_delay_ms(100); //Wait for OLED to boot
}

void main() {
    //initialize uart
    uart_configure();
    printf("\r\n Start Reaction Game \r\n");

    setup();

    //initialize debounce timer (TIM4)
    debounce_init();

    while(1) {
    }
}