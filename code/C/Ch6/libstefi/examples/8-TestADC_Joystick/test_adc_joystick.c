
#include <libstefi/adc.h>
#include <libstefi/uart.h>
#include <libstefi/peripheral.h>
#include <libstefi/util.h>

#include "stdio.h"
#include "button.h"

void setup() {
    printf("\r\n ADC Joystick, \r\n");
    adc_gpio_init(A0);
    adc_gpio_init(A1);
    adc_init(PERIPHERAL_ID_ADC1);
}

void main() {
    //initialize uart
    uart_configure();

    setup();

    while(1) {
        uint16_t x = adc_read(PERIPHERAL_ID_ADC1,5);
        uint16_t y = adc_read(PERIPHERAL_ID_ADC1,6);
        printf("x:%d, y:%d \r\n", x, y);
        soft_delay_ms(1000);
    }
}