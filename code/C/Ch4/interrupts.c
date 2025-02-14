#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "interrupts.h"

#define NUM_INTERRUPTS 240

static struct {
   struct {
        callbackfn_typeDef callback;
        void *aux_data; //use in case of gpio, timer modes like interrupt in advanced modes later
    } handlers[NUM_INTERRUPTS];
    bool initialized;
} module;

static inline uint8_t get_irq_num(void)
{
    uint8_t irq;
    __asm volatile ("mrs %0, ipsr" : "=r" (irq));
    return irq - 16;
}

void generic_dispatch()
{
    uint8_t irq_num = get_irq_num();
    module.handlers[irq_num].callback();
}

//Usage: interrupts_register_handler(TIMx_IRQn, tim_irq_handler);
void interrupts_register_handler(nvic_source_t source, callbackfn_typeDef fn)
{
    module.handlers[source].callback = fn;
}

void interrupts_init(void)
{
    for(uint8_t i = 0; i < NUM_INTERRUPTS; i++)
    {
        module.handlers[i].callback = NULL;
    }
    module.initialized = true;
}
void interrupts_global_enable(void)
{
    NVIC_GlobalEnable();
}
void interrupts_global_disable(void)
{
    NVIC_GlobalDisable();
}

void interrupts_enable_source(nvic_source_t source)
{
    NVIC_EnableIRQ(source);
}

void interrupts_disable_source(nvic_source_t source)
{
    //
}


