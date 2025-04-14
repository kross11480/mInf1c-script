#include <stddef.h>
#include "libstefi/timer.h"

#include <stdbool.h>
#include <libstefi/peripheral.h>
#include <libstefi/util.h>
#include "internal/timer_internal.h"

TIM_t *timers[] = {(TIM_t*) NULL, TIM1_BASE, TIM2_BASE, TIM3_BASE, TIM4_BASE, NULL, TIM6_BASE, TIM7_BASE, TIM8_BASE,
    NULL, NULL, NULL, NULL, NULL, NULL, TIM15_BASE, TIM16_BASE, TIM17_BASE, NULL, NULL, NULL};

static const enum _nvic_interrupt_sources timerid_to_irq[19] = {
    INTERRUPT_SOURCE_NONE,
    INTERRUPT_SOURCE_TIM1_TIM16,
    INTERRUPT_SOURCE_TIM2,
    INTERRUPT_SOURCE_TIM3,
    INTERRUPT_SOURCE_TIM4,
    INTERRUPT_SOURCE_NONE,
    INTERRUPT_SOURCE_TIM6,
    INTERRUPT_SOURCE_TIM7,
    INTERRUPT_SOURCE_TIM8,
    INTERRUPT_SOURCE_NONE,
    INTERRUPT_SOURCE_NONE,
    INTERRUPT_SOURCE_NONE,
    INTERRUPT_SOURCE_NONE,
    INTERRUPT_SOURCE_NONE,
    INTERRUPT_SOURCE_NONE,
    INTERRUPT_SOURCE_TIM15,
    INTERRUPT_SOURCE_TIM1_TIM16,
    INTERRUPT_SOURCE_TIM17,
};

static struct {
    callbackfn_typeDef callback;
} timer_handlers[NUM_TIMERINTERRUPTS];

void timer_init(const tim_id_t timer_id) {
    //ASSERT(timer_id > 0);
    assert(timer_id > 0);
    peripheral_tim_enable(timer_id);
}

void timer_start(const tim_id_t timer_id)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];

    tim->CR1 |= BIT(0);
}

void timer_stop(const tim_id_t timer_id)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];

    tim->CR1 &= ~BIT(0);
    tim->CNT = 0;
}

uint32_t timer_getcount(const tim_id_t timer_id)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];

    return tim->CNT;
}

void timer_setcount(const tim_id_t timer_id, uint32_t cnt)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];
    assert(cnt <= tim->ARR);

    tim->CNT = cnt;
}

void timer_set_period(const tim_id_t timer_id, uint16_t prescaler, uint32_t period)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];

    tim->PSC = prescaler - 1; //Set prescaler
    tim->ARR = period - 1; //Set period
    tim->CNT = 0;
}

/*******Interrupts*****************/

static inline void timer_clear_interruptflag(const tim_id_t timer_id)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];
    tim->SR &= ~BIT(0);
}

void timer_interrupt_register_handler(const tim_id_t timer_id, callbackfn_typeDef fn) {
    timer_handlers[timer_id].callback = fn;
}

static void timer_dispatch(const tim_id_t timer_id)
{
    timer_handlers[timer_id].callback();
}

static inline void handle_timer_irq(const tim_id_t timer_id) {
    timer_clear_interruptflag(timer_id);
    timer_dispatch(timer_id);
}

void timer_enable_interrupt(const tim_id_t timer_id)
{
    assert(timer_id > 0);

    TIM_t *tim = timers[timer_id];

    tim->DIER |= BIT(0); //enable interrupt
    tim->EGR |= BIT(0); //reset timer
    timer_clear_interruptflag(timer_id);
    interrupts_enable_source(timerid_to_irq[timer_id]);
}



void TIM2_IRQHandler(void) {handle_timer_irq(TIMER2);}
void TIM3_IRQHandler(void) {handle_timer_irq(TIMER3);}
void TIM4_IRQHandler(void) {handle_timer_irq(TIMER4);}
void TIM6_IRQHandler(void) {handle_timer_irq(TIMER6);}
void TIM7_IRQHandler(void) {handle_timer_irq(TIMER7);}
void TIM8_IRQHandler(void) {handle_timer_irq(TIMER8);}
void TIM15_IRQHandler(void) {handle_timer_irq(TIMER15);}
void TIM16_IRQHandler(void) {
    timer_clear_interruptflag(TIMER1);
    handle_timer_irq(TIMER16);
}
void TIM17_IRQHandler(void) {handle_timer_irq(TIMER17);}
