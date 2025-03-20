//Fading LED lights
#include "board.h"
#include "led.h"
#include "timer.h"
#include "systick.h"



void main() {
    //initialize led
    led_init(LED_GREEN);
    //portpin for red led, A0 connected to TIM2 Ch1 (AF1)
    gpio_set_alternate_function(leds[LED_GREEN].portpin, AF1);
    gpio_set_mode(leds[LED_GREEN].portpin, MODER_AF);

    timer_init_pwm(TIM2, 3, 1, 65535, 0);
    systick_init();

    timer_start(TIM2);
    systick_start();
    //initialize timer for generating PWM signal
    while(1) {
        // Fade-in
        for (int duty = 0; duty <= 100; duty++) {
            timer_set_compare(TIM2, 3, duty*655);
            systick_delay_ms(1000);
        }

        // Fade-out
        for (int duty = 100; duty >= 0; duty--) {
            //timer_set_compare(TIM2, 3, duty*655);
            //systick_delay_ms(1000);
        }
    }
}
