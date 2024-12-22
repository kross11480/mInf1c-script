//Task: Blink an LED
//Use Functions

// Task: Switch on LED connected to GPIO (PORT A, Pin 1)
// Access memory mapped peripheral register with pointer to struct
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef enum {LOW, HIGH} sig_t;
typedef enum {MODER_INPUT, MODER_OUTPUT, MODER_AF, MODER_ANALOG} moder_t;

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

void gpio_set_mode(GPIO_typeDef *gpio, uint16_t pin, moder_t mode);
void gpio_write(GPIO_typeDef *gpio, uint16_t pin, sig_t val);

void gpio_set_mode(GPIO_typeDef *gpio, uint16_t pin, moder_t mode)
{
    gpio->MODER &= ~(3<<(2*pin));
    gpio->MODER |= (mode<<(2*pin));
}

void gpio_write(GPIO_typeDef *gpio, uint16_t pin, sig_t val)
{
    gpio->BSRR = (val << pin);
}

void gpio_toggle(GPIO_typeDef *gpio, uint16_t pin)
{
    gpio->ODR ^= (1 << pin);
}

void delay(uint32_t ms) {
    uint32_t count = ms * 2000; //Approx Factor
    while (count--)
        __asm__("NOP"); //6-8 Cycles per loop => @16 Mhz
}

void main(void){
    uint16_t pin = 1; //LEDx connected to PAx in StefiLite

    //initialize gpio
    RCC->AHB2ENR |= 0x1; //Enable Clock for GPIOA
    gpio_set_mode(GPIOA, pin, MODER_OUTPUT);
    gpio_write(GPIOA, pin, HIGH);

    while (1)
    {
        gpio_toggle(GPIOA, pin);
        delay(500);
    }
}