#include "hal.h"
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

void delay_ms(uint32_t ms) {
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

sig_t debounce_button(GPIO_typeDef *gpio, uint16_t pin)
{
    static uint8_t debounce_state = HIGH; //stable state of button
    static uint8_t last_button_reading = HIGH;

    uint8_t button_current_state = gpio_read(gpio, pin);
    if (button_current_state != last_button_reading) {
        delay_ms(DEBOUNCE_TIME_MS);
        if(button_current_state == gpio_read(gpio, pin))
        {
            debounce_state = button_current_state;
        }
    }
    last_button_reading = button_current_state;
    return debounce_state;
}