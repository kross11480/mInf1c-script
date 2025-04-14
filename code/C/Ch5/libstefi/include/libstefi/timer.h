/*********************************************************************/
/* Timer Hardware Abstraction layer*/
/*********************************************************************/
#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <stdint.h>
#include "interrupts.h"

typedef enum {
    TIMER1 = 1,
    TIMER2 = 2,
    TIMER3 = 3,
    TIMER4 = 4,
    TIMER5 = -1,
    TIMER6 = 6,
    TIMER7 = 7,
    TIMER8 = 8,
    TIMER15 = 15,
    TIMER16 = 16,
    TIMER17 = 17,
} tim_id_t;

void timer_init(const tim_id_t);
void timer_start(const tim_id_t);
void timer_stop(const tim_id_t);
void timer_reset(const tim_id_t);
uint32_t timer_getcount(const tim_id_t);
void timer_setcount(const tim_id_t, uint32_t cnt);


//set prescaler and ARR according to period
void timer_set_period(const tim_id_t timer, uint16_t prescaler, uint32_t period);

void timer_enable_interrupt(const tim_id_t);
void timer_disable_interrupt(const tim_id_t);
void timer_interrupt_register_handler(const tim_id_t timer_id, callbackfn_typeDef fn);

/** Modes
void timer_change_period(tim_id_t tim, uint32_t period);
void timer_set_mode_pwm(const tim_id_t timer_id, uint32_t channel);
void timer_set_compare(const tim_id_t timer_id, uint32_t channel, uint32_t duty);
void timer_cc_enable(const tim_id_t timer_id, uint32_t channel);
void timer_init_pwm(tim_id_t tim, uint32_t channel, uint16_t prescaler, uint32_t period, uint32_t duty);
 */



#endif