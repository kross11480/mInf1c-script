#include <stdint.h>

#define BIT(num) (1 << num)

void inline soft_delay_ms(uint32_t time_in_ms) {
    uint32_t count = time_in_ms * 1865; //Approx Factor
    while (count--)
        __asm__("NOP"); //6-8 Cycles per loop => @16 Mhz
}