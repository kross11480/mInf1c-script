#include <unistd.h>
#include<stdio.h>
#include <sys/stat.h>
#include "hal.h"

//Task: Uart, Character Output @115200 Baud, 8 Bits, even parity, 1 stop bits
//Note: printf 5k, Printf_float 12K

GPIO_typeDef *port_uart_tx = GPIOA;
GPIO_typeDef *port_uart_rx = GPIOA;
uint16_t pin_uart_tx = 2;
uint16_t pin_uart_rx = 3;

typedef enum
{
    AFO,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15,
} afr_t;

void gpio_set_alternate_function(GPIO_typeDef *gpio, uint16_t pin, afr_t af)
{
    if (pin < 8)
    {
        gpio->AFR[0] |= (af << (4*pin));
    }
    else
    {
        gpio->AFR[1] |= (af << (4*(pin-8)));
    }
}

/**********************************************************************/
/* UART/USART                 Hardware Abstraction layer              */
/**********************************************************************/
typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t CR3;
    uint32_t BRR;
    uint32_t GTPR;
    uint32_t RTOR;
    uint32_t RQR;
    uint32_t ISR;
    uint32_t ICR;
    uint32_t RDR;
    uint32_t TDR;
    uint32_t PRESC;
} UART_typeDef;

void uart_configure();
void uart_poll_out(UART_typeDef *uart, unsigned char out_char);
void uart_tx(UART_typeDef *uart, const uint8_t *buf, size_t len);

#define USART1 ((UART_typeDef *) 0x40013800)
#define USART2 ((UART_typeDef *) 0x40004400)

void uart_configure(){
    //UM2397: USART2 (PA2/PA3) connected to STLINK-V3E Virtual COM port.
    RCC->APB1ENR |= (1 << 17); //switch on UART2
    RCC->APB2ENR |= (1 << 14); //UART1
    RCC->AHB2ENR |= (1 << 0); //GPIOA
    gpio_set_alternate_function(port_uart_tx, pin_uart_tx, AF7);
    gpio_set_alternate_function(port_uart_rx, pin_uart_rx, AF7);
    gpio_set_mode(port_uart_tx, pin_uart_tx, MODER_AF);
    gpio_set_mode(port_uart_rx, pin_uart_rx, MODER_AF);

    USART2->CR1 = 0;
    USART2->BRR = 139; //16000000/115200
    USART2->CR1 |= (1 << 0) | (1 << 2) | (1 << 3);

    USART1->CR1 = 0;
    USART1->BRR = 1666; //16000000/115200
    USART1->CR1 |= (1 << 0) | (1 << 2) | (1 << 3); //Transmit Enable
}

void uart_poll_out(UART_typeDef *uart, unsigned char out_char)
{
    while (1)
    {
        if(uart->ISR & (1<<7))
        break;
    }
    uart->TDR = out_char;
}

unsigned char uart_poll_in(UART_typeDef *uart)
{
    while ( (uart->ISR & (1 << 5)) != (1 << 5));
    return (unsigned char) (uart->RDR & 0xFF);
}

int _write(int file, const char *ptr, int len) {
    if (file == STDOUT_FILENO || file == STDERR_FILENO) {
        for (int i = 0; i < len; i++) {
            uart_poll_out(USART2, ptr[i]);
        }
        return len;
    }
    return -1;
}

void *_sbrk(int incr) {
    extern char _end;
    static unsigned char *heap = NULL;
    unsigned char *prev_heap;
    if (heap == NULL) heap = (unsigned char *) &_end;
    prev_heap = heap;
    heap += incr;
    return prev_heap;
}

void _fstat(int fd, struct stat *st) {}
void _close(int fd) {}
void _isatty(int fd) {}
void _lseek(int fd, int ptr, int dir) {}
void _read(int fd, char *ptr, int len) {}
void _kill(int pid, int sig) {}
void _getpid(void) {}

_Noreturn void _exit(int status) {
    (void) status;
    for (;;) __asm__ volatile("BKPT #0");
}

int main() {
    unsigned int test = 0x012346;
    float pi = 3.14;
    uart_configure();
    printf("Hello, World!%x \r\n", test); //Hex
    printf("Float: %f \r\n", pi); //float
    printf("\x1b[31m" "Hello World \x1b[0m \r\n"); //color
    printf("\x1b[0m" "Hello World \x1b[0m \r\n");
    return 0;
}
