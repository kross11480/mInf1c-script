/*********************************************************************/
/* SysTick Timer Hardware Abstraction layer*/
/*********************************************************************/
#include <stdint.h>

void systick_init();
void systick_start();
void systick_stop();
void systick_restart();


uint32_t systick_get_ms();
void systick_delay_ms(uint32_t time_in_ms);
void systick_delay_s(uint32_t time_in_s);
