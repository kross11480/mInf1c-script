#include "libstefi/gpio.h"
#include "../src/internal/gpio_internal.h"
#include <stdint.h>
#include <libstefi/peripheral.h>
#include <libstefi/util.h>

static struct {
    callbackfn_typeDef callback;
} exti_handlers[NUM_EXTIINTERRUPTS];

static inline GPIO_typeDef * gpio_get_base_address(const gpio_id_t portpin)
{
    uint16_t port = (portpin >> 8);
    uint32_t baseoffset = port * GPIO_PORTOFFSET;
    return (GPIO_typeDef *) (GPIO_BASE +  baseoffset);
}

void gpio_set_mode(const gpio_id_t portpin, moder_t mode)
{
    uint16_t pin = portpin & 0xFF;
    GPIO_typeDef *gpio = gpio_get_base_address(portpin);

    gpio->MODER &= ~(3<<(2*pin));
    gpio->MODER |= (mode<<(2*pin));
}

moder_t gpio_get_mode(const gpio_id_t portpin)
{
    uint16_t pin = portpin & 0xFF;
    GPIO_typeDef *gpio = gpio_get_base_address(portpin);

    return GET_BITS(gpio->MODER, 2*pin, 2);
}

void gpio_write(const gpio_id_t portpin, sig_t val)
{
    uint16_t pin = portpin & 0xFF;
    GPIO_typeDef *gpio = gpio_get_base_address(portpin);

    //low 16 bit odr high, upper 16 bit odr low
    gpio->BSRR = (1 << pin)<<( val ? 0: 16);
}

void gpio_toggle(const gpio_id_t portpin)
{
    uint16_t pin = portpin & 0xFF;
    GPIO_typeDef *gpio = gpio_get_base_address(portpin);

    gpio->ODR ^= (1 << pin);
}

void gpio_set_pupd(const gpio_id_t portpin, pupdr_t pupd)
{
    uint16_t pin = portpin & 0xFF;
    GPIO_typeDef *gpio = gpio_get_base_address(portpin);

    gpio->PUPDR &= ~(3<<(2*pin));
    gpio->PUPDR |= (pupd<<(2*pin));
}

sig_t gpio_read(const gpio_id_t portpin)
{
    uint16_t pin = portpin & 0xFF;
    GPIO_typeDef *gpio = gpio_get_base_address(portpin);

    return (gpio->IDR & (1<<pin) ? HIGH : LOW);
}

void gpio_set_alternate_function(const gpio_id_t portpin, afr_t af)
{
    uint16_t pin = portpin & 0xFF;
    GPIO_typeDef *gpio = gpio_get_base_address(portpin);

    if (pin < 8)
    {
        gpio->AFR[0] |= (af << (4*pin));
    }
    else
    {
        gpio->AFR[1] |= (af << (4*(pin-8)));
    }
}


void gpio_enable_interrupt(const gpio_id_t portpin, const edge_t evt) {
    uint16_t pin = portpin & 0xFF;
    uint16_t port = (portpin >> 8);
    uint16_t shift = (pin%4)*4;
    peripheral_exti_enable();

    // Initialize EXTI0 for interrupt on PB0(EXTIx = PINx)
    SYSCFG->EXTICR[pin/4] &= ~(0xF << shift); // Clear settings
    SYSCFG->EXTICR[pin/4] |= (port << shift);

    EXTI->IMR1 |= BIT(pin); 		// Enable interrupt 0 (IM).
    switch (evt) {
        case FALLING_EDGE:
            EXTI->FTSR1 |= BIT(pin);
            break;
        case RISING_EDGE:
            EXTI->RTSR1 |= BIT(pin);
            break;
    }
    	    // Trigger EXTI on falling edge
}

void gpio_clear_interruptflag(uint8_t pin) {
    EXTI->PR1 |= BIT(pin);  // Clear pending bit
}

void gpio_interrupt_register_handler(const gpio_id_t portpin, callbackfn_typeDef fn) {
    uint16_t pin = portpin & 0xFF;
    exti_handlers[pin].callback =fn;
}

void exti_dispatch(uint8_t exti_num)
{
    exti_handlers[exti_num].callback();
}

void EXTI0_IRQHandler(void)
{
    gpio_clear_interruptflag(0);
    exti_dispatch(0);
}

void EXTI1_IRQHandler(void)
{
    gpio_clear_interruptflag(1);
    exti_dispatch(1);
}

void EXTI2_IRQHandler(void)
{
    gpio_clear_interruptflag(2);
    exti_dispatch(2);
}

void EXTI3_IRQHandler(void)
{
    gpio_clear_interruptflag(3);
    exti_dispatch(3);
}

void EXTI4_IRQHandler(void)
{
    gpio_clear_interruptflag(4);
    exti_dispatch(4);
}

void EXTI5_9_IRQHandler(void) {
    for(uint8_t i = 5; i <= 9; i++) {
        if(EXTI->PR1 & BIT(i)) {
            gpio_clear_interruptflag(i);
            exti_dispatch(i);
        }
    }
}