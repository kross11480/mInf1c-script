#include "timer.h"

typedef struct {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
} SysTick_t;

typedef struct
{
  uint32_t CR1;         /*!< TIM control register 1,                   Address offset: 0x00 */
  uint32_t CR2;         /*!< TIM control register 2,                   Address offset: 0x04 */
  uint32_t SMCR;        /*!< TIM slave mode control register,          Address offset: 0x08 */
  uint32_t DIER;        /*!< TIM DMA/interrupt enable register,        Address offset: 0x0C */
  uint32_t SR;          /*!< TIM status register,                      Address offset: 0x10 */
  uint32_t EGR;         /*!< TIM event generation register,            Address offset: 0x14 */
  uint32_t CCMR1;       /*!< TIM capture/compare mode register 1,      Address offset: 0x18 */
  uint32_t CCMR2;       /*!< TIM capture/compare mode register 2,      Address offset: 0x1C */
  uint32_t CCER;        /*!< TIM capture/compare enable register,      Address offset: 0x20 */
  uint32_t CNT;         /*!< TIM counter register,                     Address offset: 0x24 */
  uint32_t PSC;         /*!< TIM prescaler,                            Address offset: 0x28 */
  uint32_t ARR;         /*!< TIM auto-reload register,                 Address offset: 0x2C */
  uint32_t RCR;         /*!< TIM repetition counter register,          Address offset: 0x30 */
  uint32_t CCR1;        /*!< TIM capture/compare register 1,           Address offset: 0x34 */
  uint32_t CCR2;        /*!< TIM capture/compare register 2,           Address offset: 0x38 */
  uint32_t CCR3;        /*!< TIM capture/compare register 3,           Address offset: 0x3C */
  uint32_t CCR4;        /*!< TIM capture/compare register 4,           Address offset: 0x40 */
  uint32_t BDTR;        /*!< TIM break and dead-time register,         Address offset: 0x44 */
  uint32_t CCR5;        /*!< TIM capture/compare register 5,           Address offset: 0x48 */
  uint32_t CCR6;        /*!< TIM capture/compare register 6,           Address offset: 0x4C */
  uint32_t CCMR3;       /*!< TIM capture/compare mode register 3,      Address offset: 0x50 */
  uint32_t DTR2;        /*!< TIM deadtime register 2,                  Address offset: 0x54 */
  uint32_t ECR;         /*!< TIM encoder control register,             Address offset: 0x58 */
  uint32_t TISEL;       /*!< TIM Input Selection register,             Address offset: 0x5C */
  uint32_t AF1;         /*!< TIM alternate function option register 1, Address offset: 0x60 */
  uint32_t AF2;         /*!< TIM alternate function option register 2, Address offset: 0x64 */
  uint32_t OR ;         /*!< TIM option register,                      Address offset: 0x68 */
  uint32_t RESERVED0[220];/*!< Reserved,                               Address offset: 0x6C */
  uint32_t DCR;         /*!< TIM DMA control register,                 Address offset: 0x3DC */
  uint32_t DMAR;        /*!< TIM DMA address for full transfer,        Address offset: 0x3E0 */
} TIM_t;

#define SysTick ((SysTick_t *) 0xE000E010)

void soft_delay_ms(uint32_t time_in_ms) {
    uint32_t count = time_in_ms * 1865; //Approx Factor
    while (count--)
        __asm__("NOP"); //6-8 Cycles per loop => @16 Mhz
}

void _systick_init()
{
    SysTick->CTRL |= (1 << 2); //1: Clock 0: Clock/8.
    SysTick->CTRL |= (1 << 1); //enable interrupt
    SysTick->LOAD = 16000; //System Core Clock=16MHz
}

void _systick_start()
{
    SysTick->VAL = 0;
    SysTick->CTRL |= (1 << 0); //start timer
}

void _systick_stop()
{
    SysTick->CTRL |= (0 << 0); //stop timer
}

void _systick_restart()
{
    _systick_stop();
    _systick_start();
}

uint32_t _systick_get_ms()
{
    uint32_t current_time = SysTick->VAL;
    return (0xFFFFFF - current_time)/TICKS_PER_MS;
}

uint32_t _systick_get_s()
{
    uint32_t current_time = SysTick->VAL;
    return (0xFFFFFF - current_time)/TICKS_PER_MS;
}

void _systick_delay_ms(uint32_t time_in_ms)
{
    while (_systick_get_ms() < time_in_ms);
    _systick_restart();
}

void timer_init(){
    _systick_init(); //Intialize Systick Clock for 16 tick per us
}

void timer_start()
{
    _systick_start();
}

void timer_stop()
{
    _systick_stop();
}

uint32_t timer_elapsed_ms()
{
    return _systick_get_ms();
}

void timer_delay_ms(uint32_t time_in_ms)
{
    _systick_delay_ms(time_in_ms);
}

void timer_delay_s(uint32_t time_in_s)
{
    for(uint32_t i = 0 ; i < time_in_s; i++)
    {
        while(!(SysTick->CTRL & (1<<16)));
    }
}
