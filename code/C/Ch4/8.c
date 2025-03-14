#include "button.h"
#include "led.h"
#include "timer.h"
#include "uart.h"
#include "stdio.h"
#include "debounce.h"

#define TIMER_ID TIM3
#define TIMER_IT INTERRUPT_SOURCE_TIM3

void s0_action() {
    //wait a random timer
    led_off(LED_RED);
    timer_start(TIMER_ID);
    while(timer_getcount(TIMER_ID) <= 1000);
    timer_reset(TIMER_ID);
    // start game
    led_on(LED_RED);
    // start reaction timer
    timer_start(TIMER_ID);
}

void s1_action() {
    led_off(LED_RED);
    printf("Reaction Time: %lu \r\n", timer_getcount(TIMER_ID));
    timer_reset(TIMER_ID);
}

void s0_callback() {
    debounce_start(BUTTON_S0, s0_action);
}


void s1_callback() {
    debounce_start(BUTTON_S1, s1_action);
}

void timer_expires() {
    printf("Slow Finger");
    timer_reset(TIMER_ID);
}

void main() {
    //initialize button
    button_init(BUTTON_S0);
    button_interrupt_init(BUTTON_S0, s0_callback);

    button_init(BUTTON_S1);
    button_interrupt_init(BUTTON_S1, s1_callback);
    //initialize led
    led_init(LED_RED);

    //initialize uart
    uart_configure();
    printf("\r\n Start Reaction Game \r\n");

    //initialize reaction timer
    timer_init(TIMER_ID);
    timer_init_periodic(TIMER_ID, TIMER_IT, timer_expires, 16000, 4000);

    //initialize debounce timer (TIM4)
    debounce_init();

    while(1) {
    }
}