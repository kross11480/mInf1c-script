#include "stdbool.h"
#include "inttypes.h"

#define LED_POS 7
#define BTN 0
#define DELAY 500

volatile uint32_t *const rcc_clock_enable = (uint32_t *) 0x4002104C;
volatile uint32_t *const gpioc_out = (uint32_t *) 0x48000814;
volatile uint32_t *const gpioc_mode = (uint32_t *) 0x48000800;
volatile uint32_t *const gpiob_in = (uint32_t *) 0x48000410;
volatile uint32_t *const gpiob_mode = (uint32_t *) 0x48000400;
volatile uint32_t *const gpiob_pullup = (uint32_t *) 0x4800040C;

bool button_state = 1;

void set_bit(volatile uint32_t *const reg, int pos){
    *reg |= (1U << pos);
}

void clear_bit(volatile uint32_t *const reg, int pos){
    *reg &= ~(1U << pos);
}

void toggle_bit(volatile uint32_t *const reg, int pos){
    *reg ^= (1U << pos);
}

void initialize(){
    /* initialize clock */
    set_bit(rcc_clock_enable, 2);
    set_bit(rcc_clock_enable, 1);
    /* initialize blue led on port C7*/
    clear_bit(gpioc_mode, 2*LED_POS+1);
    set_bit(gpioc_out, LED_POS);

    /* initialize button S0 on Port B0, mode 00(input) pullup(01)*/
    clear_bit(gpiob_mode, 2*BTN+0);
    clear_bit(gpiob_mode, 2*BTN+1);

    set_bit(gpiob_pullup, 2*BTN+0);
    clear_bit(gpiob_pullup, 2*BTN+1);
}

void sleep(uint32_t ms){
    for(int i = 0; i < 400; i++)
        for(int j = 0; j < ms; j++){
            asm("nop");
        }
}

void toggle_led(uint32_t pos){
    set_bit(gpioc_out, pos);
    sleep(DELAY);
    clear_bit(gpioc_out, pos);
    sleep(DELAY);
}

void led_off(uint32_t pos){
    set_bit(gpioc_out, pos);
    sleep(500);
}

bool button_pressed(uint32_t pos){
    uint32_t btn_value = *gpiob_in & (1U << pos);
    if(button_state & btn_value == 0){
        button_state = btn_value;
        return 1;
    } else {
        button_state = btn_value;
        return 0;
    }
}

int main(void){
    bool state = false;
    initialize();

    while(1){
        if(button_pressed(BTN) == 1){
            state = !state;
        }
        if(state){
            toggle_led(LED_POS);
        } else {
            led_off(LED_POS);
        }
    }
}