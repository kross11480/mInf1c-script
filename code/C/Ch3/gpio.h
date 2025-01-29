#include <stdint.h>

/**********************************************************************/
/* RCC (Reset Clock Control) Hardware Abstraction layer               */
/**********************************************************************/

typedef struct {
    uint32_t REGS_NOTNEEDEDNOW[19];
    uint32_t AHB2ENR;  // AHB2 peripheral clock enable register
    uint32_t AHB3ENR;  // AHB3 peripheral clock enable register
    uint32_t RESERVED;
    uint32_t APB1ENR;  // APB1 peripheral clock enable register
    uint32_t APB1ENR2;
    uint32_t APB2ENR;
} RCC_typeDef;

#define RCC ((RCC_typeDef *) 0x40021000) //Operator precedence remove ()

/**********************************************************************/
/* GPIO (General Purpose Input and Output) Hardware Abstraction layer */
/**********************************************************************/
#define GPIOA ((GPIO_typeDef *) 0x48000000) /* Base Address of Peripheral */
#define GPIOB ((GPIO_typeDef *) 0x48000400)

typedef enum {LOW, HIGH} sig_t;
typedef enum {MODER_INPUT, MODER_OUTPUT, MODER_AF, MODER_ANALOG} moder_t;
typedef enum {NONE, PULL_UP, PULL_DOWN} pupdr_t;
typedef enum {AFO, AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8, AF9, AF10, AF11, AF12, AF13, AF14, AF15,} afr_t;

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

void gpio_set_mode(GPIO_typeDef *gpio, uint16_t pin, moder_t mode);
void gpio_set_pupd(GPIO_typeDef *gpio, uint16_t pin, pupdr_t pupd);
void gpio_write(GPIO_typeDef *gpio, uint16_t pin, sig_t val);
sig_t gpio_read(GPIO_typeDef *gpio, uint16_t pin);
void gpio_toggle(GPIO_typeDef *gpio, uint16_t pin);
void gpio_set_alternate_function(GPIO_typeDef *gpio, uint16_t pin, afr_t af);
