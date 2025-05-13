#include <libstefi/gpio.h>
#include <libstefi/peripheral.h>
#include <libstefi/systick.h>
#include <libstefi/timer.h>
#include <libstefi/uart.h>
#include <libstefi/util.h>


//Timer 3 Channel 2 connected to PC7 (ds10198, Pg 94)
#define TIMER_ID TIMER3
#define LED_ID C7

void main() {
    uart_configure();
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOC);

    gpio_set_mode(LED_ID, MODER_AF);
    gpio_set_alternate_function(LED_ID, AF2);


    timer_init(TIMER_ID);
    timer_set_period(TIMER_ID, 16, 255); //PWM Freq=4 MhZ/(16*256) = 1 KHZ
    timer_set_mode_pwm(TIMER_ID, 2);
    timer_cc_enable(TIMER_ID, 2);

    timer_set_compare(TIMER_ID, 2, 0);
    timer_start(TIMER_ID);

    systick_init();
    systick_start();
    while (1) {
        // Fade-in
        for (int duty = 0; duty <255; duty++) {
            timer_set_compare(TIMER_ID, 2, duty);
            systick_delay_ms(8);
        }

        // Fade-out
        for (int duty = 256; duty > 0; duty--) {
            timer_set_compare(TIMER_ID, 2, duty);
            systick_delay_ms(8);
        }
    }
}
