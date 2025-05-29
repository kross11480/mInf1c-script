// Task: Empty Template: turning on LED1 on libstefi
#include "libstefi/gpio.h"
#include "libstefi/peripheral.h"
#include "libstefi/util.h"
#include "libstefi/system.h"

#include "internal/gpio_internal.h"
#include "internal/rcc_internal.h"

#define LED C5

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

void mco_init() {
    /* activate output of PLLCLK on MCO pin PA8/AF0 */
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOA);
    gpio_set_alternate_function(A8, AF0);
    gpio_set_mode(A8, MODER_AF);
    GPIOA->OSPEEDR |=  (0x3 << (2 * 8));        // set pin speed to very high
    RCC->CFGR       = ((RCC->CFGR & (~(0x7 << 24))) | ( BIT(24) ));
}

void main(){
    system_init();
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOC);
    gpio_set_mode(LED, MODER_OUTPUT); // LED1 on Port C pin 5 on STefi

    dwt_init();
    mco_init();

    uint32_t start = DWT_CYCCNT;
    while(1) {
        gpio_toggle(LED);
        //GPIOC->ODR ^= BIT(6);
    }
    uint32_t end = DWT_CYCCNT;
    volatile uint32_t elapsed = end - start;
}