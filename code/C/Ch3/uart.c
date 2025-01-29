/**********************************************************************/
/* UART/USART                 Hardware Abstraction layer              */
/**********************************************************************/
#include "uart.h"

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

#define USART1 ((UART_typeDef *) 0x40013800)
#define USART2 ((UART_typeDef *) 0x40004400)

//Default Uart2 on A2,A3
GPIO_typeDef *port_uart_tx = GPIOA;
GPIO_typeDef *port_uart_rx = GPIOA;
uint16_t pin_uart_tx = 2;
uint16_t pin_uart_rx = 3;
UART_typeDef *uart = USART2;

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

void uart_poll_out(unsigned char out_char)
{
    /* Check if uart is initialized */
    while (1)
    {
        if(uart->ISR & (1<<7))
            break;
    }
    uart->TDR = out_char;
}

unsigned char uart_poll_in()
{
    /* Check if uart is initialized */
    while ( (uart->ISR & (1 << 5)) != (1 << 5));
    return (unsigned char) (uart->RDR & 0xFF);
}