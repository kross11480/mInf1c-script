//Task: Blink an LED when button is pressed and switches off when pressed again
//No blocking delay, (with debouncing)
#include "hal.h"

typedef enum {OFF, TOGGLE} state_t;

void main(void){
    uint16_t pin_led = 1; //LEDx connected to PAx in StefiLite
    uint16_t pin_button = 7; //Button_x connected to PBx in StefiLite

    sig_t button_state = HIGH;
    sig_t prev_button_state = HIGH;
    state_t app_state = OFF;

    uint32_t now = 0;

    //initialize rcc, gpio, timer
    RCC->AHB2ENR |= 0x1; //Enable Clock for GPIOA
    RCC->AHB2ENR |= 0x2; //Enable Clock for GPIOB

    // set output mode for led pin and switch off led
    gpio_set_mode(GPIOA, pin_led, MODER_OUTPUT);
    gpio_write(GPIOA, pin_led, HIGH);

    //set input mode for push button
    gpio_set_mode(GPIOB, pin_button, MODER_INPUT);
    gpio_set_pupd(GPIOB, pin_button, PULL_UP);
    systick_init();

    while (1)
    {
        //read debounced button state
        button_state = debounce_button(GPIOB, pin_button);
        //Transition: if button is pressed once (edge detection), change app state
        if((button_state != prev_button_state) && (button_state == LOW))
        {
            app_state = (app_state == OFF)? TOGGLE : OFF;
            now = systick_start();
        }

        //Output: based on current app state
        switch (app_state)
        {
        case OFF:
            gpio_write(GPIOA, pin_led, HIGH);
            break;
        case TOGGLE:
            if(systick_get_millis(now) >= 500)
            {
                gpio_toggle(GPIOA, pin_led);
                // reset timer
                now = systick_start();
            }
            break;
        }
        //update previous button state for edge detection
        prev_button_state = button_state;
    }
}

