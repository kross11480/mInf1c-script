#include "libstefi/gpio.h"
#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;    // 0x00: mode register
    volatile uint32_t OTYPER;   // 0x04: GPIO output type register
    volatile uint32_t OSPEEDR;  // 0x08: GPIO output speed register
    volatile uint32_t PUPDR;    // 0x0C: GPIO pull-up/pull-down register
    volatile uint32_t IDR;      // 0x10: GPIO input data register
    volatile uint32_t ODR;      // 0x14: GPIO output data register
    volatile uint32_t BSRR;     // 0x18: GPIO bit set/reset register
    volatile uint32_t LCKR;     // 0x1C: GPIO lock register
    volatile uint32_t AFR[2];   // 0x20: GPIO alternate function registers
} GPIO_typeDef;

#define GPIO_BASE (0x48000000)
#define GPIO_PORTOFFSET (0x400)

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