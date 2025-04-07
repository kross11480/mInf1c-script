#include <stdio.h>
#include <libstefi/uart.h>

void main() {
    uart_configure();
    printf("Hallo Weelt!\r\n");
    while(1) {
    }
}
