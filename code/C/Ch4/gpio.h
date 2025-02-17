#ifndef GPIO_H
#define GPIO_H

#include "nvic.h"
#include "interrupts.h"
/**********************************************************************/
/* GPIO (General Purpose Input and Output) Hardware Abstraction layer */
/**********************************************************************/
typedef enum _stefilite_ids gpio_id_t;
typedef enum _stefi_exti_ids exti_id_t;

typedef enum {LOW, HIGH} sig_t;
typedef enum {MODER_INPUT, MODER_OUTPUT, MODER_AF, MODER_ANALOG} moder_t;
typedef enum {NONE, PULL_UP, PULL_DOWN} pupdr_t;
typedef enum {AFO, AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8, AF9, AF10, AF11, AF12, AF13, AF14, AF15,} afr_t;
typedef enum {RISING_EDGE, FALLING_EDGE} event_t;

void gpio_set_mode(const gpio_id_t portpin, moder_t mode);
void gpio_set_pupd(const gpio_id_t portpin, pupdr_t pupd);
void gpio_write(const gpio_id_t portpin, sig_t val);
sig_t gpio_read(const gpio_id_t portpin);
void gpio_toggle(const gpio_id_t portpin);
void gpio_set_alternate_function(const gpio_id_t portpin, afr_t af);

void gpio_enable_interrupt(const gpio_id_t, const event_t);
void gpio_clear_interruptflag(const exti_id_t);
void gpio_interrupt_register_handler(const nvic_source_t, callbackfn_typeDef);

enum _stefilite_ids
{
    A0 = 0x000,
    A1,
    A2,
    A3,
    A4,
    A5,
    A6,
    A7,
    A8,
    A9,
    A10,
    A11,
    A12,
    A13,
    A14,
    A15,
    B0 = 0x100,
    B1,
    B2,
    B3,
    B4,
    B5,
    B6,
    B7,
    B8,
    B9,
    B10,
    B11,
    B12,
    B13,
    B14,
    B15,
};

enum _stefi_exti_ids
{
    EXTI0 = 0,
    EXTI4 = 4,
};
#endif


