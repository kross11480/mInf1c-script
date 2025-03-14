#include "button.h"

// Callback function type for a confirmed press event
typedef void (*debounce_callback_t)();

void debounce_init();
void debounce_start(stefi_button_t button, debounce_callback_t callback);
void debounced_reaction();