#include <libstefi/spi.h>
#include <libstefi/timer.h>
#include <libstefi/uart.h>
#include <libstefi/peripheral.h>


#include "stdio.h"
#include "button.h"

void setup() {
    spi_init(PERIPHERAL_ID_SPI1, A4,A5, A6, A7);
}

void main() {
    //initialize uart
    uart_configure();
    printf("\r\n SPI Loopback PA6-PA7: Connect 13-15 on CN10, \r\n");

    setup();
    uint8_t tx_char = '0';
    while(1) {
        uint8_t rx_char = spi_transfer(PERIPHERAL_ID_SPI1, tx_char);
        if(rx_char == tx_char) {
            printf("Loopback Success \r\n");
        }
    }
}