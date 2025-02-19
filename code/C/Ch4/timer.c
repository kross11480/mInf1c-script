#include <stddef.h>
#include "timer.h"
#include "peripheral.h"
#include "util.h"
#include "interrupts.h"

//Add __weak if irq handler defined in example or main

typedef struct {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
} SysTick_t;

#define SysTick ((SysTick_t *) 0xE000E010)

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


#define TIM1_BASE ((TIM_t *) 0x40012C00)
#define TIM2_BASE ((TIM_t *) 0x40000000)
#define TIM3_BASE ((TIM_t *) 0x40000400)
#define TIM4_BASE ((TIM_t *) 0x40000800)
#define TIM5_BASE ((TIM_t *) 0x40000C00)
#define TIM6_BASE ((TIM_t *) 0x40001000)
#define TIM7_BASE ((TIM_t *) 0x40001400)
#define TIM8_BASE ((TIM_t *) 0x40013400)

#define TIM15_BASE ((TIM_t *) 0x40014000)
#define TIM16_BASE ((TIM_t *) 0x40014400)
#define TIM17_BASE ((TIM_t *) 0x40014800)


TIM_t *timers[] = {(TIM_t*) SysTick, TIM1_BASE, TIM2_BASE, TIM3_BASE, TIM4_BASE, NULL, TIM6_BASE, TIM7_BASE, TIM8_BASE,
    NULL, NULL, NULL, NULL, NULL, NULL, TIM15_BASE, TIM16_BASE, TIM17_BASE, NULL, NULL, NULL};

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

void timer_init(const tim_id_t timer){
    switch (timer)
    {
    case SYSTICK:
        _systick_init(); //Intialize Systick Clock for 16 tick per us
        break;
    case TIM1:
        peripheral_tim1_enable();
        break;
    case TIM2:
        peripheral_tim2_enable();
        break;
    case TIM3:
        peripheral_tim3_enable();
        break;
    case TIM4:
        peripheral_tim4_enable();
        break;
    case TIM6:
        peripheral_tim6_enable();
        break;
    case TIM7:
        peripheral_tim7_enable();
        break;
    case TIM8:
        peripheral_tim8_enable();
        break;
    case TIM15:
        peripheral_tim15_enable();
        break;
    case TIM16:
        peripheral_tim16_enable();
        break;
    case TIM17:
        peripheral_tim17_enable();
        break;
    default:
        break;
    }
}

void timer_set_period(const tim_id_t timer_id, uint16_t prescaler, uint32_t period)
{
    TIM_t *tim = timers[timer_id];
    switch(timer_id)
    {
    case TIM1:
    case TIM2:
    case TIM3:
    case TIM4:
    case TIM6:
    case TIM7:
    case TIM8:
    case TIM15:
    case TIM16:
    case TIM17:
        tim->PSC = prescaler - 1; //Set prescaler
        tim->ARR = period - 1; //Set period
        tim->CNT = 0;
        break;
    default:
        break;
    }
}

void timer_enable_interrupt(const tim_id_t timer_id)
{
    TIM_t *tim = timers[timer_id];
    tim->DIER |= BIT(0); //enable interrupt
    tim->EGR |= BIT(0); //reset timer
    timer_clear_interruptflag(timer_id);
}

void timer_clear_interruptflag(const tim_id_t timer_id)
{
    TIM_t *tim = timers[timer_id];
    tim->SR &= ~BIT(0);
}

void timer_start(const tim_id_t timer_id)
{
    TIM_t *tim = timers[timer_id];
    switch (timer_id)
    {
    case SYSTICK:
        _systick_start();
        break;
    case TIM1:
    case TIM2:
    case TIM3:
    case TIM4:
    case TIM5:
    case TIM6:
    case TIM7:
    case TIM8:
    case TIM15:
    case TIM16:
    case TIM17:
        tim->CR1 |= BIT(0);
        break;
    }
}

void timer_stop(const tim_id_t timer_id)
{
    TIM_t *tim = timers[timer_id];
    switch (timer_id)
    {
    case SYSTICK:
        _systick_stop();
        break;
        case TIM1:
        case TIM2:
        case TIM3:
        case TIM4:
        case TIM5:
        case TIM6:
        case TIM7:
        case TIM8:
        case TIM15:
        case TIM16:
        case TIM17:
            tim->CR1 &= ~BIT(0);
            tim->CNT = 0;
        break;
    }

}

uint32_t timer_getcount(const tim_id_t timer_id)
{
    TIM_t *tim = timers[timer_id];
    switch (timer_id)
    {
    case TIM1:
    case TIM2:
    case TIM3:
    case TIM4:
    case TIM5:
    case TIM6:
    case TIM7:
    case TIM8:
    case TIM15:
    case TIM16:
    case TIM17:
        return tim->CNT;
    default:
        break;
    }
    return 0;
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

void timer_interrupt_register_handler(const nvic_source_t tim_irq_num, callbackfn_typeDef fn)
{
    interrupts_register_handler(tim_irq_num, fn);
}

void timer_init_periodic(tim_id_t tim, nvic_source_t tim_irq_num,  callbackfn_typeDef fn, uint16_t prescaler, uint32_t period)
{
    timer_init(tim);
    timer_set_period(tim, prescaler, period);
    timer_interrupt_register_handler(tim_irq_num, fn);
}

/*********IRQ HANDLERS ***************/
void TIM2_IRQHandler(void)
{
    generic_dispatch();
    timer_clear_interruptflag(TIM2);
}

void TIM3_IRQHandler(void)
{
    generic_dispatch();
    timer_clear_interruptflag(TIM3);
}

void TIM4_IRQHandler(void)
{
    generic_dispatch();
    timer_clear_interruptflag(TIM4);
}

void TIM6_IRQHandler(void)
{
    generic_dispatch();
    timer_clear_interruptflag(TIM6);
}

void TIM7_IRQHandler(void)
{
    generic_dispatch();
    timer_clear_interruptflag(TIM7);
}

void TIM8_IRQHandler(void)
{
    generic_dispatch();
    timer_clear_interruptflag(TIM8);
}

void TIM15_IRQHandler(void)
{
    generic_dispatch();
    timer_clear_interruptflag(TIM15);
}

void TIM16_IRQHandler(void)
{
    generic_dispatch();
    timer_clear_interruptflag(TIM1);
    timer_clear_interruptflag(TIM16);
}

void TIM17_IRQHandler(void)
{
    generic_dispatch();
    timer_clear_interruptflag(TIM17);
}