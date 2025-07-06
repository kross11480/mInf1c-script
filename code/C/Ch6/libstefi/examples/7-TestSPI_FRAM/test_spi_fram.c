#include <internal/spi_internal.h>
#include <libstefi/spi.h>
#include <libstefi/timer.h>
#include <libstefi/uart.h>
#include <libstefi/peripheral.h>
#include <libstefi/util.h>

#include "stdio.h"
#include "button.h"

const uint8_t FRAM_WREN =0x6;
const uint8_t FRAM_WRDI =0x4;
const uint8_t FRAM_READ = 0x3;
const uint8_t FRAM_WRITE = 0x2;

void setup_loopback() {
    printf("\r\n SPI Loopback PA6-PA7: Connect 13-15 on CN10, \r\n");
    spi_init(PERIPHERAL_ID_SPI1, A4,A5, A6, A7);
}

void loopback() {
    uint8_t tx_char = '0';
    uint8_t rx_char = spi_transfer(PERIPHERAL_ID_SPI1, tx_char);
    if(rx_char == tx_char) {
        printf("Loopback Success \r\n");
    }
}

void fram_enable_write() {
    gpio_write(A4, LOW);
    spi_transfer(PERIPHERAL_ID_SPI1, FRAM_WREN);
    gpio_write(A4, HIGH);
}

void fram_disable_write() {
    gpio_write(A4, LOW);
    spi_transfer(PERIPHERAL_ID_SPI1, FRAM_WRDI);
    gpio_write(A4, HIGH);
}

void fram_write_byte(uint16_t addr, uint8_t data) {

    fram_enable_write();
    uint8_t msb = (addr >> 8) & 0xFF;
    uint8_t lsb = addr & 0xFF;
    gpio_write(A4, LOW);
    spi_transfer(PERIPHERAL_ID_SPI1, 0x2);
    spi_transfer(PERIPHERAL_ID_SPI1, msb);
    spi_transfer(PERIPHERAL_ID_SPI1, lsb);
    spi_transfer(PERIPHERAL_ID_SPI1, data);
    gpio_write(A4, HIGH);
    fram_disable_write();
}

uint8_t fram_read_byte(uint32_t addr) {
    uint8_t msb = (addr >> 8) & 0xFF;
    uint8_t lsb = addr & 0xFF;
    uint8_t data = 0;
    gpio_write(A4, LOW);
    spi_transfer(PERIPHERAL_ID_SPI1, 0x3);
    spi_transfer(PERIPHERAL_ID_SPI1, msb);
    spi_transfer(PERIPHERAL_ID_SPI1, lsb);
    data = spi_transfer(PERIPHERAL_ID_SPI1, 0xFF);
    gpio_write(A4, HIGH);
    return data;
}

void setup_fram_spi() {
    printf("\r\n SPI FRAM, \r\n");
    spi_init(PERIPHERAL_ID_SPI1, A4,A5, A6, A7);

    //activate FRAM
    fram_enable_write();
}

void loop_fram() {
    uint8_t tx_data = 0x42, rx_data= 12;
    bool success = true;

    for(uint32_t i =0; i < 256; i++) {
        tx_data = (uint8_t) i;
        fram_write_byte(i, tx_data);
    }

    for(uint32_t i =0; i < 256; i++) {
        rx_data = fram_read_byte(i);
        if(rx_data != i) {
            success = false;
        }
    }

    if(success) {
        printf("write successful \r\n");
    } else {
        printf("write unsuccessful:%d,%d \r\n",tx_data, rx_data);
    }
}

void main() {
    //initialize uart
    uart_configure();

    setup_fram_spi();
    //setup_loopback();
    while(1) {
        //loopback();
        loop_fram();
        soft_delay_ms(1000);
    }
}