//Task: extend interrupts to register interrupt handlers and then dispatch
// Concepts: Callback fn, Callback Data, Wrapper, Function Pointer
//Seperate library functions into low level hardware(nvic) and high level abstraction concepts(e.g. interrupt)

#include "timer.h"
#include "gpio.h"
#include "interrupts.h"
#include "peripheral.h"

uint32_t ticks = 0;
uint32_t led_red = A0;
uint32_t led_green = A2;

#define TIMER1_ID TIM3
#define TIMER1_IT INTERRUPT_SOURCE_TIM3

#define TIMER2_ID TIM4
#define TIMER2_IT INTERRUPT_SOURCE_TIM4

void led_config()
{
    peripheral_gpioA_enable(); //enable clock
    gpio_write(led_red, HIGH); //switch off led
    gpio_set_mode(led_red, MODER_OUTPUT); //set direction to output
    gpio_write(led_green, HIGH); //switch off led
    gpio_set_mode(led_green, MODER_OUTPUT); //set direction to output
}

void timer1_callback()
{
    gpio_toggle(led_red);
}

void timer2_callback()
{
    gpio_toggle(led_green);
}

void timer_init_periodic(tim_id_t tim, nvic_source_t tim_irq_num,  callbackfn_typeDef fn, uint16_t prescaler, uint32_t period)
{
    timer_init(tim);
    timer_set_period(tim, prescaler, period);
    timer_interrupt_register_handler(tim_irq_num, fn);
}

void timer_config() {
    timer_init_periodic(TIMER1_ID, TIMER1_IT, timer1_callback, 16000, 250);
    timer_init_periodic(TIMER2_ID, TIMER2_IT, timer2_callback, 16000, 500);

    //Enable Timer to fire interrupt
    timer_enable_interrupt(TIMER1_ID);
    timer_enable_interrupt(TIMER2_ID);
}

void system_init()
{
    interrupts_init();
    interrupts_global_disable();

    led_config(); //Configure LEDs
    timer_config(); //Configure Timers

    interrupts_global_enable();

    //enable NVIC to pass interrupt
    interrupts_enable_source(TIMER1_IT);
    interrupts_enable_source(TIMER2_IT);
}

void main(void){
    system_init();

    timer_start(TIMER1_ID);
    timer_start(TIMER2_ID);

    while(1)
    {
    }
}