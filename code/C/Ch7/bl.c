// Task: Empty Template: turning on LED1 on libstefi
#include <libstefi/util.h>
#include "libstefi/components/simple_io/pin.h"

#define LED B8
void main(){
    pin_init(LED, PIN_OUT);
    while(1) {
        pin_set_value(LED, HIGH);
        soft_delay_ms(500);
        pin_set_value(LED, LOW);
        soft_delay_ms(500);
    }
}