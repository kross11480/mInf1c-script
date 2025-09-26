#include <pin.h>

pin_id_t left_tracker_pin = A15;
pin_id_t right_tracker_pin = B6;
void tracker_init(){
    pin_init(left_tracker_pin, PIN_IN);
    pin_init(right_tracker_pin, PIN_IN);
}
int read_left_tracker() {
    return gpio_read(left_tracker_pin);
}
int read_right_tracker() {
    return gpio_read(right_tracker_pin);
}