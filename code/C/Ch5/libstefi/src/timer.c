#include <stddef.h>
#include "libstefi/timer.h"

#include <assert.h>
#include <stdbool.h>
#include <libstefi/peripheral.h>
#include <libstefi/util.h>

#include "internal/timer_internal.h"

TIM_t *timers[] = {(TIM_t*) NULL, TIM1_BASE, TIM2_BASE, TIM3_BASE, TIM4_BASE, NULL, TIM6_BASE, TIM7_BASE, TIM8_BASE,
    NULL, NULL, NULL, NULL, NULL, NULL, TIM15_BASE, TIM16_BASE, TIM17_BASE, NULL, NULL, NULL};

void timer_init(const tim_id_t timer_id) {
    peripheral_tim_enable(timer_id);
}

void timer_start(const tim_id_t timer_id)
{
    assert(timers[timer_id] != NULL);
    TIM_t *tim = timers[timer_id];

    tim->CR1 |= BIT(0);
}

void timer_stop(const tim_id_t timer_id)
{
    assert(timers[timer_id] != NULL);
    TIM_t *tim = timers[timer_id];

    tim->CR1 &= ~BIT(0);
    tim->CNT = 0;
}

uint32_t timer_getcount(const tim_id_t timer_id)
{
    assert(timers[timer_id] != NULL);
    TIM_t *tim = timers[timer_id];

    return tim->CNT;
}

void timer_setcount(const tim_id_t timer_id, uint32_t cnt)
{
    assert(timers[timer_id] != NULL);
    TIM_t *tim = timers[timer_id];
    assert(cnt <= tim->ARR);

    tim->CNT = cnt;
}

void timer_set_period(const tim_id_t timer_id, uint16_t prescaler, uint32_t period)
{
    assert(timers[timer_id] != NULL);
    TIM_t *tim = timers[timer_id];

    tim->PSC = prescaler - 1; //Set prescaler
    tim->ARR = period - 1; //Set period
    tim->CNT = 0;
}
