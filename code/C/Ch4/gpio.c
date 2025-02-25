#include "gpio.h"
#include <stdint.h>
#include <stddef.h>
#include "peripheral.h"
#include "util.h"

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
#define GPIOB ((GPIO_typeDef *) 0x48000400)

typedef struct
{
    volatile uint32_t IMR1;        /*!< EXTI Interrupt mask register 1,             Address offset: 0x00 */
    volatile uint32_t EMR1;        /*!< EXTI Event mask register 1,                 Address offset: 0x04 */
    volatile uint32_t RTSR1;       /*!< EXTI Rising trigger selection register 1,   Address offset: 0x08 */
    volatile uint32_t FTSR1;       /*!< EXTI Falling trigger selection register 1,  Address offset: 0x0C */
    volatile uint32_t SWIER1;      /*!< EXTI Software interrupt event register 1,   Address offset: 0x10 */
    volatile uint32_t PR1;         /*!< EXTI Pending register 1,                    Address offset: 0x14 */
    uint32_t      RESERVED1;   /*!< Reserved, 0x18                                                   */
    uint32_t      RESERVED2;   /*!< Reserved, 0x1C                                                   */
    volatile uint32_t IMR2;        /*!< EXTI Interrupt mask register 2,             Address offset: 0x20 */
    volatile uint32_t EMR2;        /*!< EXTI Event mask register 2,                 Address offset: 0x24 */
    volatile uint32_t RTSR2;       /*!< EXTI Rising trigger selection register 2,   Address offset: 0x28 */
    volatile uint32_t FTSR2;       /*!< EXTI Falling trigger selection register 2,  Address offset: 0x2C */
    volatile uint32_t SWIER2;      /*!< EXTI Software interrupt event register 2,   Address offset: 0x30 */
    volatile uint32_t PR2;         /*!< EXTI Pending register 2,                    Address offset: 0x34 */
} EXTI_typeDef;

#define EXTI ((EXTI_typeDef *) 0x40010400)

typedef struct
{
    volatile uint32_t MEMRMP;      /*!< SYSCFG memory remap register,                        Address offset: 0x00      */
    volatile uint32_t CFGR1;       /*!< SYSCFG configuration register 1,                     Address offset: 0x04      */
    volatile uint32_t EXTICR[4];   /*!< SYSCFG external interrupt configuration registers,   Address offset: 0x08-0x14 */
    volatile uint32_t SCSR;        /*!< SYSCFG CCMSRAM control and status register,          Address offset: 0x18      */
    volatile uint32_t CFGR2;       /*!< SYSCFG configuration register 2,                     Address offset: 0x1C      */
    volatile uint32_t SWPR;        /*!< SYSCFG CCMSRAM write protection register,            Address offset: 0x20      */
    volatile uint32_t SKR;         /*!< SYSCFG CCMSRAM Key Register,                         Address offset: 0x24      */
} SYSCFG_typeDef;

#define SYSCFG ((SYSCFG_typeDef *) 0x40010000)

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

void gpio_enable_interrupt(const gpio_id_t portpin, const event_t evt) {
    uint16_t pin = portpin & 0xFF;
    uint16_t port = (portpin >> 8);
    uint16_t shift = (pin%4)*4;
    peripheral_exti_enable();

    // Initialize EXTI0 for interrupt on PB0(EXTIx = PINx)
    SYSCFG->EXTICR[pin/4] &= ~(0xF << shift); // Clear settings
    SYSCFG->EXTICR[pin/4] |= (port << shift);

    EXTI->IMR1 |= BIT(pin); 		// Enable interrupt 0 (IM).
    EXTI->FTSR1 |= BIT(pin); 	    // Trigger EXTI on falling edge
}

void gpio_clear_interruptflag(const exti_id_t pin) {
    EXTI->PR1 |= BIT(pin);  // Clear pending bit
}

void gpio_interrupt_register_handler(const exti_id_t exti_id, callbackfn_typeDef fn) {
    exti_handlers[exti_id].callback =fn;
}

void exti_dispatch(uint8_t exti_num)
{
    exti_handlers[exti_num].callback();
}

void EXTI0_IRQHandler(void)
{
    gpio_clear_interruptflag(EXTI0);
    exti_dispatch(0);

}

void EXTI4_IRQHandler(void)
{
    gpio_clear_interruptflag(EXTI4);
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
