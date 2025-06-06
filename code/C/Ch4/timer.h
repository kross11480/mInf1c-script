/*********************************************************************/
/* SysTick Timer Hardware Abstraction layer*/
/*********************************************************************/
#include <stdint.h>
#include "interrupts.h"

typedef enum _timer_ids tim_id_t;

void timer_init(const tim_id_t);

void timer_enable_interrupt(const tim_id_t);
void timer_clear_interruptflag(const tim_id_t);
void timer_interrupt_register_handler(const nvic_source_t, callbackfn_typeDef);

//set prescaler and ARR according to period
void timer_set_period(const tim_id_t timer, uint16_t prescaler, uint32_t period);
void timer_change_period(tim_id_t tim, uint32_t period);
void timer_set_mode_pwm(const tim_id_t timer_id, uint32_t channel);
void timer_set_compare(const tim_id_t timer_id, uint32_t channel, uint32_t duty);
void timer_cc_enable(const tim_id_t timer_id, uint32_t channel);

void timer_init_periodic(tim_id_t tim, nvic_source_t tim_irq_num,  callbackfn_typeDef fn, uint16_t prescaler, uint32_t period);
void timer_init_pwm(tim_id_t tim, uint32_t channel, uint16_t prescaler, uint32_t period, uint32_t duty);


void timer_start(const tim_id_t);
void timer_reset(const tim_id_t);
uint32_t timer_getcount(const tim_id_t);

uint32_t timer_elapsed_ms();
void timer_delay_ms(uint32_t time_in_ms);
void timer_delay_s(uint32_t time_in_s);

enum _timer_ids
{
    TIM1 = 1,
    TIM2 = 2,
    TIM3 = 3,
    TIM4 = 4,
    TIM5 = -1,
    TIM6 = 6,
    TIM7 = 7,
    TIM8 = 8,
    TIM15 = 15,
    TIM16 = 16,
    TIM17 = 17,
};