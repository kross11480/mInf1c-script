//Task: Refactor gpio drive to include port pin id in a single enum
//Note: Comment out compiler option add_link_options(-u _printf_float) for linker errors
//Note: Keep mask and shift, optimize later
#include "gpio.h"

void main(){
    RCC->AHB2ENR |= (1 << 1);
    gpio_set_mode(B8, MODER_OUTPUT);
    gpio_write(B8, HIGH);
}


