#include <unistd.h>
#include <stdio.h>
#include "uart.h"
//Task: Split HAL into seperate files
//Note: What should be included in header, function prototype
//Note: function implementation in c, otherwise linker error undefined def

int main() {
    unsigned int test = 0x012346;
    float pi = 3.14;
    uart_configure();
    printf("Hello, World! %x \r\n", test); //Hex
    printf("Float: %f \r\n", pi); //float
    printf("\x1b[31m" "Hello World \x1b[0m \r\n"); //color
    printf("\x1b[0m" "Hello World \x1b[0m \r\n");
    return 0;
}
