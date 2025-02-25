//Library problem:
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

void user_led_off() {
    led_off(LED_RED);
    led_off(LED_YELLOW);
    led_off(LED_GREEN);
    led_off(LED_BLUE);
}
void state_action() {
    switch (state) {
        case OFF:
            //stop the timer, no interrupts, no toggling
            user_led_off();
            timer_reset(TIMER_ID);
            break;
        case LED_RED_1_HZ:
            user_led_off();
            timer_init_periodic(TIMER_ID, TIMER_IT, timer_expires, 16000, 500);
            timer_start(TIMER_ID);
            break;
        case LED_YELLLOW_2_HZ:
            user_led_off();
            timer_init_periodic(TIMER_ID, TIMER_IT, timer_expires, 16000, 250);
            timer_start(TIMER_ID);
            break;
        case LED_GREEN_4_HZ:
            user_led_off();
            timer_init_periodic(TIMER_ID, TIMER_IT, timer_expires, 16000, 125);
            timer_start(TIMER_ID);
            break;
        case LED_BLUE_8_HZ:
            user_led_off();
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
    //State transition
    button_todebounce = BUTTON_S0;
    timer_start(DEB_TIMER_ID);
}

void s1_callback() {
    button_todebounce = BUTTON_S1;
    timer_start(DEB_TIMER_ID);
}

void debounced_toggle() {
    timer_reset(DEB_TIMER_ID); //reset timer
    bool debounced_state_is_pressed = button_is_pressed(button_todebounce);
    if (debounced_state_is_pressed) {
        if (button_todebounce == BUTTON_S0) {
            g_event = S0_pressed;
        }
        if (button_todebounce == BUTTON_S1) {
            g_event = S1_pressed;
        }
    }

    //state transition
    if(g_event == S0_pressed && state < NUM_STATE) {
        state++;
    }

    if(g_event == S1_pressed && state > OFF) {
        state--;
    }
    //State Action: Change timer period based on the state
    state_action();
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

    timer_init(TIMER_ID);

    //initialize debounce timer to 10ms
    timer_init_periodic(DEB_TIMER_ID, DEB_TIMER_IT, debounced_toggle, 16000, 40);

    while(1) {
    }
}
