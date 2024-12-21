typedef unsigned int uint32_t;

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

typedef struct {
    uint32_t REGS_NOTNEEDEDNOW[19];
    uint32_t AHB2ENR;  // AHB2 peripheral clock enable register
} RCC_typeDef;

/* Base Address of Peripheral */
#define GPIOA ((GPIO_typeDef *) 0x48000000)
#define RCC ((RCC_typeDef *) 0x40021000) //Operator precedence remove ()

int main(void){
    unsigned int pin = 0; //LED connected to PA0
    //initialize gpio
    RCC->AHB2ENR |= 0x1; //Enable Clock for GPIOA
    GPIOA->MODER &= ~(3<<(2*pin));
    GPIOA->MODER |= (0x1<<(2*pin));

    //switch on led 0
    GPIOA->ODR &= ~(0x1<<pin);

    return 0;
}