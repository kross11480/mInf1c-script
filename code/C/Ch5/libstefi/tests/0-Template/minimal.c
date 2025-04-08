#include <stdio.h>
#include <libstefi/uart.h>

void main() {
    uart_configure();
    printf("Hallo Welt!\r\n");
    while(1) {
    }
}
