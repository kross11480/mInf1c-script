#include "libstefi/gpio.h"
#include "../src/internal/gpio_internal.h"
#include <stdint.h>
#include <libstefi/peripheral.h>
#include <libstefi/util.h>

// define the opaque type
struct gpio_port {
    GPIO_typeDef* regs;  // Embed actual port register layout
};

static gpio_port_t gpio_ports[] = {
    {GPIOA},
    {GPIOB},
    {GPIOC},
};

gpio_pin_t gpio_init(const gpio_id_t portpin) {
    gpio_pin_t p = {.port = &gpio_ports[portpin >> 8], .pin = portpin & 0xFF};
    return p;
}

void gpio_set_mode(const gpio_pin_t *portpin, moder_t mode) {
    uint16_t pin = portpin->pin;
    GPIO_typeDef *gpio = (GPIO_typeDef *) portpin->port->regs;
    gpio->MODER &= ~(3<<(2*pin));
    gpio->MODER |= (mode<<(2*pin));
}

void gpio_toggle(const gpio_pin_t *portpin)
{
    uint16_t pin = portpin->pin;
    GPIO_typeDef *gpio = (GPIO_typeDef *) portpin->port->regs;

    gpio->ODR ^= (1 << pin);
}

static struct {
    callbackfn_typeDef callback;
} exti_handlers[NUM_EXTIINTERRUPTS];

void gpio_clear_interruptflag(uint8_t pin) {
    EXTI->PR1 |= BIT(pin);  // Clear pending bit
}

static void exti_dispatch(uint8_t exti_num)
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

void EXTI10_15_IRQHandler(void) {
    for(uint8_t i = 10; i <= 15; i++) {
        if(EXTI->PR1 & BIT(i)) {
            gpio_clear_interruptflag(i);
            exti_dispatch(i);
        }
    }
}