//Task: Refactor gpio driver to include port pin id in a single enum
//Task: Refactor uart and timer driver
//Note: Comment out compiler option add_link_options(-u _printf_float) for linker errors
//Note: Keep mask and shift, optimize later
#include "gpio.h"
#include "uart.h"
#include "timer.h"
#include <stdio.h>

void main(){
    RCC->AHB2ENR |= (1 << 1);
    //Test GPIO
    gpio_set_mode(B8, MODER_OUTPUT);
    gpio_write(B8, HIGH);

    //Test UART
    uart_configure();
    printf("Hello World!! \r\n");

    //Test Timer
    timer_init();
    timer_start();
    while(1)
    {
        gpio_toggle(B8);
        timer_delay_ms(10);
    }
}


