#include "libstefi/peripheral.h"

#include "led.h"
#include "board.h"
//Functions
void led_init(stefi_led_t id) {
    uint16_t port = gpio_get_port(leds[id].portpin);
    peripheral_gpio_enable(port);
    gpio_write(leds[id].portpin, leds[id].off_state);
    gpio_set_mode(leds[id].portpin, MODER_OUTPUT);
}
void led_on(stefi_led_t id) {
    gpio_write(leds[id].portpin, !leds[id].off_state);
}

void led_off(stefi_led_t id) {
    gpio_write(leds[id].portpin, leds[id].off_state);
}

void led_toggle(stefi_led_t id) {
    gpio_toggle(leds[id].portpin);
}

void user_led_set(uint8_t mask) {

}