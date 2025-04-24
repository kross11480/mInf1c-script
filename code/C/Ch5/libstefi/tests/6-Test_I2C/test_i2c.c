#include <libstefi/uart.h>
#include <libstefi/util.h>
#include <libstefi/i2c.h>

#include "stdint.h"
#include "stdio.h"

#define LM75_ADDR 0x48
#define I2C_ID 2
#define SCL A9
#define SDA A8

//For repeat Check https://cued-partib-device-programming.readthedocs.io/en/latest/i2c-com-lm75.html
int main(void) {
    uint8_t rx_value[2] = {1,1};
    uint8_t tx_value[2] = {0x00,0x00};



    uart_configure();
    i2c_init(I2C_ID, SCL, SDA); // configure I2C2: PA9(scl), PA8(sda)

    printf(" --Read Temperature from LM75 -- \r\n");

    uint8_t reg_addr = 0x00;
    i2c_writeto(I2C_ID, LM75_ADDR, &reg_addr, 1, true);
    i2c_readfrom(I2C_ID, LM75_ADDR, rx_value, 2);

    while (1) {

        i2c_readfrom(I2C_ID, LM75_ADDR, rx_value, 2);
        int16_t raw = (rx_value[0] << 8) | rx_value[1];
        float temp_c = raw / 256.0f;
        printf("Read Temperature:%f \r\n", temp_c);

        soft_delay_ms(5000);
    }
    return 1;
}

