#define TIMER_ID TIMER5
#define LED_ID C4
#include <stdio.h>
#include <libstefi/gpio.h>
#include <libstefi/peripheral.h>
#include <libstefi/timer.h>
#include <libstefi/uart.h>
#include <libstefi/util.h>
#include <internal/timer_internal.h>

void timer_callback()
{
    gpio_toggle(LED_ID);
}

void main() {
    uart_configure();
    printf("Test timer interrupts: %d \r\n", TIMER_ID);
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOC);
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOB);
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOA);

    gpio_set_mode(LED_ID, MODER_OUTPUT);

    timer_init(TIMER_ID);
    timer_set_period(TIMER_ID, 4000, 500);
    timer_interrupt_register_handler(TIMER_ID, timer_callback);
    timer_enable_interrupt(TIMER_ID);

    timer_start(TIMER_ID);

    while (1) {
    }
}
