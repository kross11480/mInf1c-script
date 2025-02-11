/*********************************************************************/
/* SysTick Timer Hardware Abstraction layer*/
/*********************************************************************/
#include <stdint.h>

#define TICKS_PER_S 16000000
#define TICKS_PER_MS 16000
#define TICKS_PER_US 16

typedef enum _timer_ids tim_id_t;

void timer_init(const tim_id_t);
void timer_init(const tim_id_t);
void timer_enable_interrupt(const tim_id_t);
void timer_clear_interruptflag(const tim_id_t);

//set prescaler and ARR according to period
void timer_set_period(const tim_id_t timer, uint16_t prescaler, uint32_t period);
void timer_set_mode(); //periodic, oc, ic, pwm

//void timer_set, uint32_t prescaler, uint32_t period
void timer_start(const tim_id_t);
void timer_stop(const tim_id_t);
uint32_t timer_getcount(const tim_id_t);

uint32_t timer_elapsed_ms();
void timer_delay_ms(uint32_t time_in_ms);
void timer_delay_s(uint32_t time_in_s);
void soft_delay_ms(uint32_t time_in_ms);

enum _timer_ids
{
    SYSTICK = 0,
    TIM1,
    TIM2,
    TIM3,
    TIM4,
    TIM5,
    TIM6,
    TIM7,
};