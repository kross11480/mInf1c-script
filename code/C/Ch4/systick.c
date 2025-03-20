/*********************************************************************/
/* SysTick Timer Hardware Abstraction layer*/
/*********************************************************************/
#include <stdint.h>
#include "systick.h"

#define TICKS_PER_S 16000000
#define TICKS_PER_MS 16000
#define TICKS_PER_US 16

//Add __weak if irq handler defined in example or main
typedef struct {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
} SysTick_t;

#define SysTick ((SysTick_t *) 0xE000E010)

void systick_init()
{
    SysTick->CTRL |= (1 << 2); //1: Clock 0: Clock/8.
    SysTick->CTRL |= (1 << 1); //enable interrupt
    SysTick->LOAD = 16000; //System Core Clock=16MHz
}

void systick_start()
{
    SysTick->VAL = 0;
    SysTick->CTRL |= (1 << 0); //start timer
}

void systick_stop()
{
    SysTick->CTRL |= (0 << 0); //stop timer
}

void systick_restart()
{
    systick_stop();
    systick_start();
}

uint32_t systick_get_ms()
{
    uint32_t current_time = SysTick->VAL;
    return (0xFFFFFF - current_time)/TICKS_PER_MS;
}

void systick_delay_ms(uint32_t time_in_ms)
{
    while (systick_get_ms() < time_in_ms);
    systick_restart();
}

void systick_delay_s(uint32_t time_in_s)
{
    for(uint32_t i = 0 ; i < time_in_s; i++)
    {
        while(!(SysTick->CTRL & (1<<16)));
    }
}