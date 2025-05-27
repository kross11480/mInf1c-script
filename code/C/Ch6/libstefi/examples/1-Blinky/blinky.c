// Task: Empty Template: turning on LED1 on libstefi
#include "libstefi/gpio.h"
#include "libstefi/peripheral.h"
#include "libstefi/util.h"
#include "internal/gpio_internal.h"



// Define CMSIS addresses manually if not using CMSIS
#define DWT_CTRL    (*(volatile uint32_t*)0xE0001000)
#define DWT_CYCCNT  (*(volatile uint32_t*)0xE0001004)
#define DEMCR       (*(volatile uint32_t*)0xE000EDFC)
#define DEMCR_TRCENA   (1 << 24)
#define DWT_CTRL_CYCCNTENA (1 << 0)

void dwt_init(void) {
    // Enable DWT and the cycle counter
    DEMCR |= DEMCR_TRCENA;           // Enable trace and debug blocks
    DWT_CTRL |= DWT_CTRL_CYCCNTENA;  // Enable the cycle counter
    DWT_CYCCNT = 0;                  // Reset the counter
}

#define LED C6
void main(){
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOC);
    gpio_set_mode(LED, MODER_OUTPUT); // LED1 on Port C pin 5 on STefi

    dwt_init();

    uint32_t start = DWT_CYCCNT;
    for(uint32_t i = 0; i <1000; i++) {
        gpio_toggle(LED);
        //GPIOC->ODR ^= BIT(6);
    }
    uint32_t end = DWT_CYCCNT;
    volatile uint32_t elapsed = end - start;
}