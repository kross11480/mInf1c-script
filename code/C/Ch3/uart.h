#include <stddef.h>
#include <stdint.h>

void uart_configure();
void uart_poll_out(unsigned char out_char);
void uart_tx(const uint8_t *buf, size_t len);


