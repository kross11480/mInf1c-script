//Fading LED lights
#include "board.h"
#include "led.h"
#include "timer.h"

void timer_init_pwm(tim_id_t tim, uint32_t channel, uint16_t prescaler, uint32_t period, uint32_t duty)
{
    uint32_t pwm_width = .01 * duty * period;
    timer_init(tim);
    timer_set_period(tim, prescaler, period);
    timer_set_mode_pwm(tim, channel);
    timer_set_compare(tim, channel, pwm_width);
    timer_cc_enable(tim, channel);
}

void main() {
    //initialize led
    led_init(LED_RED);
    //portpint for red led, A0 connected to TIM2 Ch1 (AF1)
    gpio_set_alternate_function(leds[LED_RED].portpin, AF1);
    gpio_set_mode(leds[LED_RED].portpin, MODER_AF);
    timer_init_pwm(TIM2, 1, 16000, 1000, 500);
    //initialize timer for generating PWM signal
    while(1) {
    }
}
