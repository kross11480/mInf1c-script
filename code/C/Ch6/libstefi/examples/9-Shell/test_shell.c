
#include <led.h>
#include <libstefi/uart.h>
#include <libstefi/peripheral.h>
#include <libstefi/util.h>

#include "shell.h"

void setup() {

}

void main() {
    //initialize uart
    uart_configure();
    led_init(LED0_RED, OUTPUT);

    shell_init();

    while(1) {
        shell_run();
    }
}