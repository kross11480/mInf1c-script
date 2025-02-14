
#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include "nvic.h"

//Datatypes
typedef void (*callbackfn_typeDef)();

//Functions
void interrupts_init(void);
void interrupts_global_enable(void);
void interrupts_global_disable(void);

void interrupts_enable_source(nvic_source_t source);
void interrupts_disable_source(nvic_source_t source);
void interrupts_register_handler(nvic_source_t source, callbackfn_typeDef fn);
void generic_dispatch();
#endif
