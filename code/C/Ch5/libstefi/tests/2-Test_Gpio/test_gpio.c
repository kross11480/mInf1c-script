#include <string.h>
#include <internal/rcc_internal.h>
#include <libstefi/util.h>
#include "libstefi/uart.h"
#include "libstefi/gpio.h"
#include "stdio.h"
#include "internal/gpio_internal.h"

void main() {
    uart_configure();

    printf("----Testing GPIO ---- \r\n");
    gpio_set_mode(C4, MODER_OUTPUT);
    ASSERT(0x0 == gpio_get_mode(C4));

    while(1) {
    }
}