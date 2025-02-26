//Library problem:
//* Do not forget /r/n in printf to flush data
//* return from irq on spurious irq signals or debounce fail
//* printf for test
//* init overwriting exti handler
//* state action should not depend on previous state therefore all led's 0
//* debouncing
//a program that causes the STefi Light System LEDs to flash in five stages at different frequencies.
// Button 2 increases the level, button 1 decreases it.
// The flashing frequency may change by exactly one level each time a button is pressed.
// View the four LEDs simultaneously as a binary display which indicates the current flashing frequency in Hertz.
// LED0 represents the LSB. Realize the frequencies 0 Hz / LEDs off, 1 Hz / LED0, 2 Hz / LED1, 4 Hz / LED2 and 8 Hz / LED3.

#include "button.h"
#include "led.h"
#include "timer.h"
#include "stdio.h"
#include "uart.h"

//Function
void s0_callback();
void s1_callback();
void timer_expires();

typedef enum {
    OFF = 0,
    LED_RED_1_HZ = 1,
    LED_YELLLOW_2_HZ = 2,
    LED_GREEN_4_HZ = 3,
    LED_BLUE_8_HZ = 4,
    NUM_STATE = 5,
} app_state_t;

typedef enum {
    S0_pressed,
    S1_pressed,
} app_event_t;

app_state_t state = OFF;
app_event_t g_event;
stefi_button_t button_todebounce;

#define TIMER_ID TIM3
#define TIMER_IT INTERRUPT_SOURCE_TIM3

#define DEB_TIMER_ID TIM4
#define DEB_TIMER_IT INTERRUPT_SOURCE_TIM4

#define PERF_TIMER_ID TIM6
#define PERF_TIMER_IT INTERRUPT_SOURCE_TIM6

void user_led_off() {
    led_off(LED_RED);
    led_off(LED_YELLOW);
    led_off(LED_GREEN);
    led_off(LED_BLUE);
}
void state_action() {
    user_led_off();
    timer_reset(TIMER_ID);
    switch (state) {
        case OFF:
            break;
        case LED_RED_1_HZ:
            timer_init_periodic(TIMER_ID, TIMER_IT, timer_expires, 16000, 500);
            timer_start(TIMER_ID);
            break;
        case LED_YELLLOW_2_HZ:
            timer_init_periodic(TIMER_ID, TIMER_IT, timer_expires, 16000, 250);
            timer_start(TIMER_ID);
            break;
        case LED_GREEN_4_HZ:
            timer_init_periodic(TIMER_ID, TIMER_IT, timer_expires, 16000, 125);
            timer_start(TIMER_ID);
            break;
        case LED_BLUE_8_HZ:
            timer_init_periodic(TIMER_ID, TIMER_IT, timer_expires, 16000, 63);
            timer_start(TIMER_ID);
            break;
        default:
            break;
    }
}

void timer_expires() {
    switch(state) {
        case LED_RED_1_HZ:
            gpio_toggle(LED_RED);
            break;
        case LED_YELLLOW_2_HZ:
            gpio_toggle(LED_YELLOW);
            break;
        case LED_GREEN_4_HZ:
            gpio_toggle(LED_GREEN);
            break;
        case LED_BLUE_8_HZ:
            gpio_toggle(LED_BLUE);
            break;
        default:
            break;
    }
}

void s0_callback() {
    timer_start(DEB_TIMER_ID);
    timer_start(PERF_TIMER_ID);
    button_todebounce = BUTTON_S0;
}

void s1_callback() {
    timer_start(DEB_TIMER_ID);
    button_todebounce = BUTTON_S1;
}

void debounced_toggle() {
    timer_reset(DEB_TIMER_ID); //reset timer
    bool debounced_state_is_pressed = button_is_pressed(button_todebounce);
    if(!debounced_state_is_pressed)
        return;
    switch(button_todebounce) {
        case BUTTON_S0:
            g_event = S0_pressed;
            break;
        case BUTTON_S1:
            g_event = S1_pressed;
            break;
        default:
            break;
    }
    //state transition
    if(g_event == S0_pressed && state < NUM_STATE - 1) {
        state++;
        printf("New State: %d \r\n", state);
        state_action();
    } else if(g_event == S1_pressed && state > OFF) {
        state--;
        printf("New State: %d \r\n", state);
        state_action();
    }
}

void perf_timer_overflow() {
}

void main() {

    led_init(LED_RED);
    led_init(LED_YELLOW);
    led_init(LED_GREEN);
    led_init(LED_BLUE);

    button_init(BUTTON_S0);
    button_init(BUTTON_S1);
    button_interrupt_init(BUTTON_S0, s0_callback);
    button_interrupt_init(BUTTON_S1, s1_callback);

    //uart_configure();
    printf("Start Flashing Light App \r\n");

    //initialize debounce timer to 10ms
    timer_init(TIMER_ID);
    timer_init_periodic(DEB_TIMER_ID, DEB_TIMER_IT, debounced_toggle, 16000, 40);
    timer_init_periodic(PERF_TIMER_ID, PERF_TIMER_IT, perf_timer_overflow, 16000, 5000);

    while(1) {
    }
}
