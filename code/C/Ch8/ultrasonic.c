#include "ultrasonic.h"

#include <libstefi/util.h>

static ultrasonic_config_t config;

volatile uint16_t ticks = 0;
uint16_t trigger = 0;
static enum { WAIT_FOR_RISING, WAIT_FOR_FALLING } state = WAIT_FOR_RISING;
static uint16_t rising = 0, falling = 0;

void capture_callback()
{
    uint16_t current_capture_value = 0;
    const int capture_timer = config.tim;
    const uint8_t capture_channel = config.channel;

    current_capture_value = timer_get_compare(capture_timer, capture_channel);

    if (state == WAIT_FOR_RISING) {
        rising = current_capture_value;
        timer_set_ic_edge(capture_timer, capture_channel, TIMER_EDGE_FALLING);
        state = WAIT_FOR_FALLING;
    } else {
        falling = current_capture_value;
        if (falling >= rising)
            ticks = falling - rising;
        else
            ticks = (timer_get_arr(capture_timer) - rising + falling);
        timer_set_ic_edge(capture_timer, capture_channel, TIMER_EDGE_RISING);
        state = WAIT_FOR_RISING;
        trigger = 0;
    }
}

void ultrasonic_init(pin_id_t echo_pin, pin_id_t trig_pin, tim_id_t capture_timer, timer_channel_t capture_channel) {
    config.trig_pin = trig_pin;
    config.echo_pin = echo_pin;
    config.tim = capture_timer;
    config.channel = capture_channel;

    pin_init(trig_pin, PIN_OUT);
    pin_init(echo_pin, PIN_ALT);
    pin_set_alt(echo_pin, AF10);

    timer_init(capture_timer);
    timer_set_mode_ic(capture_timer, capture_channel);
    timer_cc_interrupt_register_handler(capture_timer, capture_channel, capture_callback);
    timer_cc_enable(capture_timer, capture_channel, true);
    timer_start(capture_timer);
}

int ultrasonic_measure() {
    gpio_write(config.trig_pin, LOW); soft_delay_us(8);
    gpio_write(config.trig_pin, HIGH); soft_delay_us(80);
    gpio_write(config.trig_pin, LOW);
    trigger = 1;
    soft_delay_ms(1);
    int distance;
    if(trigger == 0) {
        //Factor: 0.125 as CPU Clock: 4MHz + round trip time
        distance = (ticks * 0.03125) * 0.0343f;
    } else {
        distance = 9999;
    }
    return distance;
}

