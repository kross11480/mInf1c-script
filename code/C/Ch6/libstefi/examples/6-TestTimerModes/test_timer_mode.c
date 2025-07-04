#include <internal/timer_internal.h>
#include <libstefi/board.h>
#include <libstefi/peripheral.h>
#include <libstefi/rng.h>
#include <libstefi/systick.h>
#include <libstefi/timer.h>
#include <libstefi/uart.h>
#include <libstefi/util.h>

#include "stdio.h"
#include "led.h"
#include "button.h"

#define LED LED3_BLUE
#define OUT_PIN C11 //OC1B: Pin 6 on J1
#define CAPTURE_PIN C9 //OC2: Pin 8 on J1

volatile uint16_t ticks;
const int capture_timer = TIMER3;
const uint8_t capture_channel = 4;

void setup_fadinglights() {
    led_init(LED, PWM);

    systick_init();
    systick_start();
}

void fading_lights() {
    // Fade-in
    for (int duty = 0; duty <255; duty++) {
        led_set_brightness(LED, duty);
        systick_delay_ms(8);
    }

    // Fade-out
    for (int duty = 256; duty > 0; duty--) {
        led_set_brightness(LED, duty);
        systick_delay_ms(8);
    }
}

void timer_callback()
{
    gpio_toggle(OUT_PIN);
}

void capture_callback()
{
    static uint16_t last_capture_value = 0, current_capture_value = 0;
    current_capture_value = timer_get_compare(capture_timer, capture_channel);

    if(last_capture_value < current_capture_value)
    {
        ticks = current_capture_value - last_capture_value;
    }
    else
    {
        ticks = (timer_get_arr(capture_timer) - last_capture_value) + current_capture_value;
    }
    last_capture_value = current_capture_value;
}

void setup() {
    //Setup Timer6 to send 100KhZ Square wave on C11
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOC);
    gpio_set_mode(OUT_PIN, MODER_OUTPUT);

    timer_init(TIMER6);
    timer_set_period(TIMER6, 40, 49); //Timer Freq= 100 KHZ, Out Freq= 1 Khz
    timer_interrupt_register_handler(TIMER6, timer_callback);
    timer_enable_interrupt(TIMER6);
    timer_start(TIMER6);

    //Setup Timer3 to capture input on C9
    gpio_set_mode(C9, MODER_AF);
    gpio_set_alternate_function(C9, AF2);

    timer_init(capture_timer);
    timer_set_mode_ic(capture_timer, capture_channel);
    timer_cc_interrupt_register_handler(capture_timer, capture_channel, capture_callback);
    timer_cc_enable(capture_timer, capture_channel, true);
    timer_start(capture_timer);
}

void main() {
    //initialize uart
    uart_configure();
    printf("\r\n Start PWM-based LED fading/input capture \r\n");

    setup();

    while(1) {
        printf("Ticks:%d \r\n", 4000000/ticks);
    }
}