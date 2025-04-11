#define TIMER_ID TIMER2
#define LED_ID C4
#include <stdio.h>
#include <libstefi/gpio.h>
#include <libstefi/peripheral.h>
#include <libstefi/timer.h>
#include <libstefi/uart.h>
#include <libstefi/util.h>
#include <internal/timer_internal.h>

void main() {
    uart_configure();
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOC);
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOB);
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOA);

    gpio_set_mode(LED_ID, MODER_OUTPUT);

    timer_init(TIMER_ID);
    timer_set_period(TIMER_ID, 4000, 500);
    timer_start(TIMER_ID);

    while (1) {
        // Wait until timer reaches 200 (or wraps)
        while (timer_getcount(TIMER_ID) != 200) {
        }
        gpio_toggle(LED_ID);
        timer_setcount(TIMER_ID, 0);
    }
}
