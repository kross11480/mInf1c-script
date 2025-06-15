#include "button.h"

#define DEB_TIMER_ID TIMER6
#define DEB_PSC 4000
#define DEB_PERIOD 10

// Callback function type for a confirmed press event
typedef void (*debounce_callback_t)();

void debounce_init();
void debounce_start(stefi_button_t button, debounce_callback_t callback);