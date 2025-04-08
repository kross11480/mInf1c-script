// Task: Empty Template: turning on LED1 on libstefi
#include <stdio.h>
#include <libstefi/systick.h>
#include <libstefi/uart.h>

#include "libstefi/gpio.h"
#include "libstefi/peripheral.h"
#include "libstefi/board.h"

#define BLINK_PERIOD 500
void main(){
    uart_configure();
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOC);
    gpio_set_mode(LED0, MODER_OUTPUT);

    //Start SysTick timer for use in Polling mode
    systick_init();
    systick_start();

    uint32_t current = systick_get_ms();
    while (1) {
        //blocking delay
        //systick_delay_ms(1); //blocking delay
        //gpio_toggle(LED0);

        //Non-blocking delay
        if(systick_expired(&current, BLINK_PERIOD)) {
            //Library toggle takes 70 cycles
            printf("Toggle time, t: %ld \r\n", current);
            gpio_toggle(LED0);
        }
    }
}