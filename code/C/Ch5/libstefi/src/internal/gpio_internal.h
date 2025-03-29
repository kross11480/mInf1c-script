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

//For compatibility, low level test code
#define GPIOA ((GPIO_typeDef *) 0x48000000)
#define GPIOB ((GPIO_typeDef *) 0x48000400)
#define GPIOC ((GPIO_typeDef *) 0x48000800)