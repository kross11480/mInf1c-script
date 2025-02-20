//Task: Use Interrupts and Debouncing to implement the traffic light example

#include "led.h"
#include "button.h"
#include "timer.h"

typedef enum state {
    GREEN,
    GREEN_WAIT,
    RED,
    YELLOW,
    YELLOWRED,
    BLUERED,
} tl_state_t;

typedef enum {
    BUTTON_PRESSED,
    TIMER_GREEN_EXPIRES,
    TIMER_YELLOW_EXPIRES,
    TIMER_RED_EXPIRES,
    TIMER_YELLOWRED_EXPIRES,
    TIMER_BLUERED_EXPIRES,
} tl_event_t;

tl_event_t g_event;
tl_state_t current_state = GREEN;

#define DELAY_RED 2000
#define DELAY_YELLOW 2000
#define DELAY_GREEN 5000
#define DELAY_YELLOWRED 2000
#define DELAY_BLUERED 1000

#define TIMER_ID TIM3
#define TIMER_IT INTERRUPT_SOURCE_TIM3

#define DEB_TIMER_ID TIM4
#define DEB_TIMER_IT INTERRUPT_SOURCE_TIM4

void state_transition(void) {
    tl_state_t next_state = current_state;
    switch (g_event) {
        case BUTTON_PRESSED:
            if(current_state ==  GREEN) {
                next_state = GREEN_WAIT;
            }
            break;
        case TIMER_GREEN_EXPIRES:
            if(current_state ==  GREEN_WAIT) {
                next_state = YELLOW;
            }
            break;
        case TIMER_YELLOW_EXPIRES:
            if(current_state ==  YELLOW) {
                next_state = RED;
            }
            break;
        case TIMER_RED_EXPIRES:
            if(current_state ==  RED) {
                next_state = BLUERED;
            }
            break;
        case TIMER_BLUERED_EXPIRES:
            if(current_state ==  BLUERED) {
                next_state = YELLOWRED;
            }
            break;
        case TIMER_YELLOWRED_EXPIRES:
            if(current_state ==  YELLOWRED) {
                next_state = GREEN;
            }
            break;
        default:
            break;
    }
    current_state = next_state;
}

void state_action(void) {
    switch (current_state) {
        case GREEN: //tlight green
            led_on(LED_GREEN);
            led_off(LED_YELLOW);
            led_off(LED_RED);
            break;
        case GREEN_WAIT:
            timer_change_period(TIMER_ID, DELAY_GREEN);
            timer_start(TIMER_ID);
            break;
        case YELLOW: //tlight yellow
            led_on(LED_YELLOW);
            led_off(LED_GREEN);
            led_off(LED_RED);
            timer_change_period(TIMER_ID, DELAY_YELLOW);
            timer_start(TIMER_ID);
            break;
        case RED:
            led_on(LED_RED);
            led_off(LED_YELLOW);
            led_off(LED_GREEN);
            timer_change_period(TIMER_ID, DELAY_RED);
            timer_start(TIMER_ID);
            break;
        case BLUERED: //tl red, pl blue
            led_on(LED_BLUE);
            led_on(LED_RED);
            led_off(LED_YELLOW);
            led_off(LED_GREEN);
            timer_change_period(TIMER_ID, DELAY_BLUERED);
            timer_start(TIMER_ID);
            break;
        case YELLOWRED:
            led_off(LED_BLUE);
            led_on(LED_RED);
            led_on(LED_YELLOW);
            led_off(LED_GREEN);
            timer_change_period(TIMER_ID, DELAY_YELLOWRED);
            timer_start(TIMER_ID);
            break;
        default:
            break;
    }
}

void button_callback() {
    timer_start(DEB_TIMER_ID);
}

void debounced_toggle() {
    timer_reset(DEB_TIMER_ID); //reset timer
    bool debounced_state_is_pressed = button_is_pressed(BUTTON_S0);
    if (debounced_state_is_pressed) {
        g_event = BUTTON_PRESSED;
    }
    state_transition();
    state_action();
}

void TL_timer_expires() {
    timer_reset(TIMER_ID); //reset timer
    switch (current_state) {
        case GREEN_WAIT: g_event = TIMER_GREEN_EXPIRES; break;
        case YELLOW: g_event = TIMER_YELLOW_EXPIRES; break;
        case RED: g_event = TIMER_RED_EXPIRES; break;
        case YELLOWRED: g_event = TIMER_YELLOWRED_EXPIRES; break;
        case BLUERED: g_event = TIMER_BLUERED_EXPIRES; break;
        default: break;
    }
    state_transition();
    state_action();
}


void main() {
    led_init(LED_RED);
    led_init(LED_YELLOW);
    led_init(LED_GREEN);
    led_init(LED_BLUE);

    button_init(BUTTON_S0);
    button_interrupt_init(BUTTON_S0, button_callback);

    //initialize debounce timer to 10ms
    timer_init_periodic(DEB_TIMER_ID, DEB_TIMER_IT, debounced_toggle, 16000, 10);

    //initialize timer to delay for green
    timer_init_periodic(TIMER_ID, TIMER_IT, TL_timer_expires, 16000, DELAY_GREEN);

    while (1) {
    }
}
