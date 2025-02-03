/*********************************************************************/
/* SysTick Timer Hardware Abstraction layer*/
/*********************************************************************/
#include <stdint.h>

#define TICKS_PER_S 16000000
#define TICKS_PER_MS 16000
#define TICKS_PER_US 16

/* Assume System Clock of 16 Mhz for timer_init */
void timer_init();
void timer_start();
void timer_stop();
uint32_t timer_elapsed_ms();
void timer_delay_ms(uint32_t time_in_ms);
void timer_delay_s(uint32_t time_in_s);
void soft_delay_ms(uint32_t time_in_ms);