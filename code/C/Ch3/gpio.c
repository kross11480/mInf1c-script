#include "gpio.h"

void gpio_set_mode(GPIO_typeDef *gpio, uint16_t pin, moder_t mode)
{
    gpio->MODER &= ~(3<<(2*pin));
    gpio->MODER |= (mode<<(2*pin));
}

void gpio_write(GPIO_typeDef *gpio, uint16_t pin, sig_t val)
{
    //low 16 bit odr high, upper 16 bit odr low
    gpio->BSRR = ((1 << pin))<<( val ? 0: 16);
}

void gpio_toggle(GPIO_typeDef *gpio, uint16_t pin)
{
    gpio->ODR ^= (1 << pin);
}

void gpio_set_pupd(GPIO_typeDef *gpio, uint16_t pin, pupdr_t pupd)
{
    gpio->PUPDR &= ~(3<<(2*pin));
    gpio->PUPDR |= (pupd<<(2*pin));
}

sig_t gpio_read(GPIO_typeDef *gpio, uint16_t pin)
{
    return (gpio->IDR & (1<<pin) ? HIGH : LOW);
}

void gpio_set_alternate_function(GPIO_typeDef *gpio, uint16_t pin, afr_t af)
{
    if (pin < 8)
    {
        gpio->AFR[0] |= (af << (4*pin));
    }
    else
    {
        gpio->AFR[1] |= (af << (4*(pin-8)));
    }
}