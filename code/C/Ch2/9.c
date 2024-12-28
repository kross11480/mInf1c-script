//Task: Blink an LED when button is pressed and switches off when pressed again
//No blocking delay, (with debouncing)
#include "hal.h"

typedef enum {OFF, LED_CHASER} state_t;
#define NUM_LEDS 4
#define PERIOD 250

GPIO_typeDef *port_led[NUM_LEDS] = {GPIOA, GPIOA, GPIOA, GPIOA};
uint16_t pin_led[NUM_LEDS] = {0, 1, 2, 3};
GPIO_typeDef *port_button = GPIOB;
uint16_t pin_button = 7; //Button_x connected to PBx in StefiLite
void setup(void);

void setup(void)
{
    //initialize rcc, gpio, timer
    RCC->AHB2ENR |= 0x1; //Enable Clock for GPIOA
    RCC->AHB2ENR |= 0x2; //Enable Clock for GPIOB

    // set output mode for led pin and switch off led
    for(uint32_t i = 0; i < NUM_LEDS; i++){
        gpio_set_mode(port_led[i], pin_led[i], MODER_OUTPUT);
        gpio_write(port_led[i], pin_led[i], HIGH);
    }

    //set input mode for push button
    gpio_set_mode(port_button, pin_button, MODER_INPUT);
    gpio_set_pupd(port_button, pin_button, PULL_UP);
    systick_init();
}

void main(void){

    sig_t button_state;
    sig_t prev_button_state = HIGH;
    state_t app_state = OFF;
    uint32_t now = 0;
    uint16_t j = 0;
    int dir = 1;

    setup();

    while (1)
    {
        //read debounced button state
        button_state = debounce_button(GPIOB, pin_button);
        //Transition: if button is pressed once (edge detection), change app state
        if((button_state != prev_button_state) && (button_state == LOW))
        {
            app_state = (app_state == OFF)? LED_CHASER : OFF;
            now = systick_start();
        }

        //Output: based on current app state
        switch (app_state)
        {
        case OFF:
            for(uint32_t i = 0; i < NUM_LEDS; i++)
            {
                gpio_write(port_led[i], pin_led[i], HIGH);
            }
            j = 1;
            dir = -1;
            break;
        case LED_CHASER:
            if(systick_get_millis(now) >= PERIOD)
            {
                j += dir;

                gpio_write(port_led[j], pin_led[j], LOW);
                gpio_write(port_led[j-dir], pin_led[j-dir], HIGH);

                // reset timer
                now = systick_start();
                //update direction of LEDs
                if(j == NUM_LEDS - 1)
                {
                    dir = -1;
                }
                if(j == 0)
                {
                    dir = 1;
                }
            }
            break;
        }
        //update previous button state for edge detection
        prev_button_state = button_state;
    }
}

