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
    callbackfn_typeDef callback[TIMER_IRQ_MAX];
    void *aux_data;
} timer_handlers[NUM_TIMERINTERRUPTS] = {0};

void timer_init(const tim_id_t timer_id) {
    //ASSERT(timer_id > 0);
    assert(timer_id > 0);
    peripheral_tim_enable(timer_id);
}

void timer_start(const tim_id_t timer_id)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];

    tim->SR = 0;
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

uint32_t timer_get_arr(const tim_id_t timer_id) {
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];

    return tim->ARR;
}

uint32_t timer_get_compare(const tim_id_t timer_id, timer_channel_t channel)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];
    uint32_t val = 0;
    switch(channel) {
        case 1: val = tim->CCR1; break;
        case 2: val = tim->CCR2; break;
        case 3: val = tim->CCR3; break;
        case 4: val = tim->CCR4; break;
        default: break;
    }
    return val;
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
    //assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];

    tim->PSC = prescaler - 1; //Set prescaler
    tim->ARR = period - 1; //Set period
    tim->CNT = 0;
    tim->EGR |= BIT(0);  // Load new ARR immediately
}

void timer_set_mode_opm(const tim_id_t timer_id) {
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];

    tim->CR1 |= BIT(3);
}

void timer_wait_for_update_flag(const tim_id_t timer_id) {
    //assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];

    while (!(tim->SR & BIT(0)));
    tim->SR = 0; // Clear flag
}

void timer_set_mode_pwm(const tim_id_t timer_id, timer_channel_t channel)
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

void timer_set_mode_ic(const tim_id_t timer_id, timer_channel_t channel)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];
    tim->PSC = 0;
    tim->ARR = 0xFFFF;
    tim->CR1 |= BIT(7); // ARPE: enable shadow registers of ARR

    uint8_t shift = (channel & 1) ? 0 : 8;
    //set mode
    if (channel == 1 || channel == 2) {
        tim->CCMR1 &= ~(3 << shift);
        tim->CCMR1 |= 1 << shift; // CC1 or 2 configured as input, IC1,2 mapped on TI1,2
        tim->CCMR1 &= ~(0xF << (shift+4)); //reset input capture filter
        tim->CCMR1 |= (0x1 << (shift+4)); //0b0001: fSAMPLING=fCK_INT, N=2 consective event validate a transition
    } else {
        tim->CCMR2 &= ~(3 << shift);
        tim->CCMR2 |= 1 << shift; // CC3 or 4 configured as input, IC3,4 mapped on TI3,4
        tim->CCMR2 &= ~(0xF << (shift+4)); //reset input capture filter
        tim->CCMR2 |= (0x1 << (shift+4)); //0b0001: fSAMPLING=fCK_INT, N=2 consective event validate a transition
    }

}

void timer_set_compare(const tim_id_t timer_id, timer_channel_t channel, uint32_t duty)
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

static void timer_set_cc_io(const tim_id_t timer_id, uint32_t channel, bool is_input, uint8_t shift) {
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];
    volatile uint8_t polarity = 1;
    if(is_input) {
        // CC1NP=0, CC1P=0: sensitive to rising edge
        tim->CCER &= ~(0x1 << (shift + 1)| 0x1  << (shift+3));
        // enable capture from counter in capture register
        tim->CCER |= BIT(shift); //enable input
        tim->DIER |= BIT(channel); // enable cc1 interrupt generation
    } else {
        tim->CCER |= polarity << (shift + 1);  // OC signal is active low
        tim->CCER |= BIT(shift); //enable output
        if(timer_id == 1 || timer_id == 8) {
            tim->BDTR |= BIT(15); //Master Output Enable
        }
    }
}

void timer_set_ic_edge(const tim_id_t timer_id, timer_channel_t channel, timer_edge_t edge) {
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];
    uint8_t shift = (channel -1) * 4;
        // CC1NP=0, CC1P=0: sensitive to rising edge
    if(edge == TIMER_EDGE_RISING) {
        tim->CCER &= ~(0x1 << (shift + 1)| 0x1  << (shift+3));
    } else if(edge == TIMER_EDGE_FALLING) {
        tim->CCER |= 0x1 << (shift + 1);
    }
}

/*******Interrupts*****************/
void timer_interrupt_register_handler(const tim_id_t timer_id, callbackfn_typeDef fn) {
    timer_handlers[timer_id].callback[TIMER_UPDATE_IRQ] = fn;
}

void timer_cc_interrupt_register_handler(const tim_id_t timer_id, timer_interrupt_t channel, callbackfn_typeDef fn) {
    timer_handlers[timer_id].callback[channel] = fn;
}

static void timer_dispatch(const tim_id_t timer_id, const timer_interrupt_t irq_type)
{
    timer_handlers[timer_id].callback[irq_type]();
}

static inline void timer_clear_interruptflag(const tim_id_t timer_id) {
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];
    uint32_t interrupt_flag = tim->SR;
    if ((interrupt_flag & BIT(0)) && timer_handlers[timer_id].callback[TIMER_UPDATE_IRQ]) {
        tim->SR &= ~BIT(0);
    }
    if ((interrupt_flag & BIT(1)) && timer_handlers[timer_id].callback[TIMER_CC1_IRQ]) {
        tim->SR &= ~BIT(1);
    }
    if ((interrupt_flag & BIT(2)) && timer_handlers[timer_id].callback[TIMER_CC2_IRQ]) {
        tim->SR &= ~BIT(2);
    }
    if ((interrupt_flag & BIT(3)) && timer_handlers[timer_id].callback[TIMER_CC3_IRQ]) {
        tim->SR &= ~BIT(3);
    }
    if ((interrupt_flag & BIT(4)) && timer_handlers[timer_id].callback[TIMER_CC4_IRQ]) {
        tim->SR &= ~BIT(4);
    }
}

static inline void handle_timer_irq(const tim_id_t timer_id) {
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];
    uint32_t interrupt_flag = tim->SR;
    if ((interrupt_flag & BIT(0)) && timer_handlers[timer_id].callback[TIMER_UPDATE_IRQ]) {
        tim->SR &= ~BIT(0);
        timer_dispatch(timer_id, 0);
    }
    if ((interrupt_flag & BIT(1)) && timer_handlers[timer_id].callback[TIMER_CC1_IRQ]) {
        tim->SR &= ~BIT(1);
        timer_dispatch(timer_id, 1);
    }
    if ((interrupt_flag & BIT(2)) && timer_handlers[timer_id].callback[TIMER_CC2_IRQ]) {
        tim->SR &= ~BIT(2);
        timer_dispatch(timer_id, 2);
    }
    if ((interrupt_flag & BIT(3)) && timer_handlers[timer_id].callback[TIMER_CC3_IRQ]) {
        tim->SR &= ~BIT(3);
        timer_dispatch(timer_id, 3);
    }
    if ((interrupt_flag & BIT(4)) && timer_handlers[timer_id].callback[TIMER_CC4_IRQ]) {
        tim->SR &= ~BIT(4);
        timer_dispatch(timer_id, 4);
    }
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

void timer_cc_enable(const tim_id_t timer_id, timer_channel_t channel, bool is_input)
{
    assert(timer_id > 0);
    TIM_t *tim = timers[timer_id];
    uint8_t shift;

    switch(channel) {
        case 1:
            shift = 0;
        timer_set_cc_io(timer_id, channel, is_input, shift);
        break;
        case 2:
            shift = 4;
        timer_set_cc_io(timer_id, channel, is_input, shift);
        break;
        case 3:
            shift = 8;
        timer_set_cc_io(timer_id, channel, is_input, shift);
        break;
        case 4:
            shift = 12;
        timer_set_cc_io(timer_id, channel, is_input, shift);
        break;
        default:
            break;
    }

    tim->CR1 |= BIT(7); // ARPE: Enable auto-reload preload & UPDATE GENERATION
    tim->EGR |= BIT(0); //reset timer: preloads the shadow registers
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
