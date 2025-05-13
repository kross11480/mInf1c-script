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
    tim->ARR = period; //Set period
    tim->CNT = 0;
}

void timer_set_mode_pwm(const tim_id_t timer_id, uint32_t channel)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];

    uint8_t shift = (channel & 1) ? 0 : 8;
    uint8_t mode = 6; //0110 = PWM Mode 1, add mode 2 later
    //set mode
    if (channel == 1 || channel == 2) {
        tim->CCMR1 |=  mode << (shift+4);       // OCM2 field = PWM
        tim->CCMR1 |= BIT(3) << shift; // Output compare 1 preload enable
    } else {
        tim->CCMR2 |=  mode << (shift + 4);       // OCM2 field = PWM
        tim->CCMR2 |= BIT(3) << shift; // Output compare 2 preload enable}
    }
}

void timer_set_compare(const tim_id_t timer_id, uint32_t channel, uint32_t duty)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];

    //set compare register
    switch(channel) {
        case 1:
            tim->CCR1 = duty;
            break;
        case 2:
            tim->CCR2 = duty;
            break;
        case 3:
            tim->CCR3 = duty;
            break;
        case 4:
            tim->CCR4 = duty;
            break;
        default:
            break;
        }
}

void timer_cc_enable(const tim_id_t timer_id, uint32_t channel)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];
    uint8_t shift;
    uint8_t polarity = 1; //

    switch(channel) {
        case 1:
            shift = 0;
            tim->CCER |= polarity << (shift + 1);    // OC signal is active low
            tim->CCER |= BIT(0) << (shift); //OC is output
            break;
        case 2:
            shift = 4;
            tim->CCER |= polarity << (shift + 1);    // OC signal is active low
            tim->CCER |= BIT(0) << (shift); //OC is output
            break;
        case 3:
            shift = 8;
            tim->CCER |= polarity << (shift + 1);    // OC signal is active low
            tim->CCER |= BIT(0) << (shift); //OC is output
            break;
        case 4:
            shift = 12;
            tim->CCER |= polarity << (shift + 1);    // OC signal is active low
            tim->CCER |= BIT(0) << (shift); //OC is output
            break;
        default:
            break;
    }
    // Enable auto-reload preload & UPDATE GENERATION
    tim->CR1 |= BIT(7); // ARPE
    tim->EGR |= BIT(0); // UG: update registers
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
