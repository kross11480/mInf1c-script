
/* *******************************************************************************
 * The LSBs of the temperature value go to LED3..0
 *******************************************************************************/
#include <internal/gpio_internal.h>
#include <internal/rcc_internal.h>
#include <internal/i2c_internal.h>
#include <libstefi/uart.h>
#include <libstefi/util.h>
#include <libstefi/i2c.h>

#include "stdint.h"
#include "stdio.h"


int main(void) {
    const uint8_t slave_addr = 0x48; // 7-bit address of LM75
    uint8_t rx_value[2] = {0, 0};

    uart_configure();
    printf(" --Read Temperature from LM75 -- \r\n");
    i2c_init(2, A9, A8); // configure I2C2: PA9(scl), PA8(sda)

    while (1) {
        i2c_readfrom(2, slave_addr, rx_value, 2);
        printf("Read Temperature:%d \r\n", rx_value[0]);
        soft_delay_ms(5000);
    }
    return 1;
}

