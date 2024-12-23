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

typedef struct {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
} SysTick_t;

/* Base Address of Peripheral */
#define GPIOA ((GPIO_typeDef *) 0x48000000)
#define RCC ((RCC_typeDef *) 0x40021000) //Operator precedence remove ()
#define SysTick ((SysTick_t *) 0xE000E010)

#define TICKS_PER_MS 16000

void gpio_set_mode(GPIO_typeDef *gpio, uint16_t pin, moder_t mode);
void gpio_write(GPIO_typeDef *gpio, uint16_t pin, sig_t val);
void gpio_toggle(GPIO_typeDef *gpio, uint16_t pin);
void delay(uint32_t ms);

void systick_init();
uint32_t systick_start();
uint32_t systick_get_elapsedtime_ms(uint32_t start);
void systick_delay_ms(uint32_t start, uint32_t time_in_ms);

void systick_init()
{
    SysTick->CTRL |= (1 << 2); //1: Clock 0: Clock/8.
    SysTick->CTRL |= (1 << 0); //start timer
    SysTick->LOAD = 0xFFFFFF;
}

uint32_t systick_start()
{
    uint32_t start = SysTick->VAL;
    return start;
}

void systick_delay_ms(uint32_t start, uint32_t time_in_ms)
{
    while (systick_get_elapsedtime_ms(start) < time_in_ms);
}

uint32_t systick_get_elapsedtime_ms(uint32_t start)
{
    uint32_t current_time = SysTick->VAL;
    if (current_time < start)
        return (start - current_time)/TICKS_PER_MS;
    else
        return (start + (0xFFFFFF - current_time))/TICKS_PER_MS;
}

void main(void){
    uint16_t pin = 1; //LEDx connected to PAx in StefiLite
    uint32_t start = 0;

    //initialize rcc, gpio, timer
    RCC->AHB2ENR |= 0x1; //Enable Clock for GPIOA
    gpio_set_mode(GPIOA, pin, MODER_OUTPUT);
    gpio_write(GPIOA, pin, HIGH);
    systick_init();

    while (1)
    {
        start = systick_start();
        gpio_toggle(GPIOA, pin);
        systick_delay_ms(start, elapsed_time);
    }
}

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
    uint32_t count = ms * 1865; //Approx Factor
    while (count--)
        __asm__("NOP"); //6-8 Cycles per loop => @16 Mhz
}