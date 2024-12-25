//Task: Blink an LED when button is pressed and switches off when released
//Do not use blocking delay, but elapsed time so as to read buttons (withOUT debouncing)

// Task: Switch on LED connected to GPIO (PORT A, Pin 1)
// Access memory mapped peripheral register with pointer to struct
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef enum {LOW, HIGH} sig_t;
typedef enum {MODER_INPUT, MODER_OUTPUT, MODER_AF, MODER_ANALOG} moder_t;
typedef enum {NONE, PULL_UP, PULL_DOWN} pupdr_t;

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
#define GPIOB ((GPIO_typeDef *) 0x48000400)

#define RCC ((RCC_typeDef *) 0x40021000) //Operator precedence remove ()
#define SysTick ((SysTick_t *) 0xE000E010)

#define TICKS_PER_MS 16000

void gpio_set_mode(GPIO_typeDef *gpio, uint16_t pin, moder_t mode);
void gpio_set_pupd(GPIO_typeDef *gpio, uint16_t pin, pupdr_t pupd);
void gpio_write(GPIO_typeDef *gpio, uint16_t pin, sig_t val);
sig_t gpio_read(GPIO_typeDef *gpio, uint16_t pin);
void gpio_toggle(GPIO_typeDef *gpio, uint16_t pin);

void delay(uint32_t ms);

void systick_init();
uint32_t systick_start();
void systick_stop();
uint32_t systick_get_millis(uint32_t start);
void systick_delay_ms(uint32_t start, uint32_t time_in_ms);


void main(void){
    uint16_t pin_led = 1; //LEDx connected to PAx in StefiLite
    uint16_t pin_button = 7; //Button_x connected to PBx in StefiLite

    sig_t button_state = HIGH;
    sig_t prev_button_state = HIGH;

    uint32_t now = 0;



    //initialize rcc, gpio, timer
    RCC->AHB2ENR |= 0x1; //Enable Clock for GPIOA
    RCC->AHB2ENR |= 0x2; //Enable Clock for GPIOB

    // set output mode for led pin and switch off led
    gpio_set_mode(GPIOA, pin_led, MODER_OUTPUT);
    gpio_write(GPIOA, pin_led, HIGH);

    //set input mode for push button
    gpio_set_mode(GPIOB, pin_button, MODER_INPUT);
    gpio_set_pupd(GPIOB, pin_button, PULL_UP);
    systick_init();

    while (1)
    {
        button_state = gpio_read(GPIOB, pin_button);
        //if state changes and timer not running, start timer
        if((button_state != prev_button_state))
        {
            now = systick_start();
            gpio_write(GPIOA, pin_led, HIGH);
        }
        switch (button_state)
        {
        case HIGH:
            systick_stop();
            break;
        case LOW:
            if(systick_get_millis(now) >= 500)
            {
                gpio_toggle(GPIOA, pin_led);
                // reset timer
                now = systick_start();
            }
            break;
        }
        prev_button_state = button_state;
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

void gpio_set_pupd(GPIO_typeDef *gpio, uint16_t pin, pupdr_t pupd)
{
    gpio->PUPDR &= ~(3<<(2*pin));
    gpio->PUPDR |= (pupd<<(2*pin));
}

sig_t gpio_read(GPIO_typeDef *gpio, uint16_t pin)
{
    return (gpio->IDR & (1<<pin) ? HIGH : LOW);
}

void delay(uint32_t ms) {
    uint32_t count = ms * 1865; //Approx Factor
    while (count--)
        __asm__("NOP"); //6-8 Cycles per loop => @16 Mhz
}

void systick_init()
{
    SysTick->CTRL |= (1 << 2); //1: Clock 0: Clock/8.
    SysTick->LOAD = 0xFFFFFF;
}

uint32_t systick_start()
{
    SysTick->CTRL |= (1 << 0); //start timer
    uint32_t start = SysTick->VAL;
    return start;
}

void systick_stop()
{
    SysTick->CTRL |= (0 << 0); //stop timer
}

void systick_delay_ms(uint32_t start, uint32_t time_in_ms)
{
    while (systick_get_millis(start) < time_in_ms);
}

uint32_t systick_get_millis(uint32_t start)
{
    uint32_t current_time = SysTick->VAL;
    if (current_time < start)
        return (start - current_time)/TICKS_PER_MS;
    else
        return (start + (0xFFFFFF - current_time))/TICKS_PER_MS;
}