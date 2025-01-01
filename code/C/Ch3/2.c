#include "hal.h"
#include "stddef.h"

//Task: Uart, Character Output @115200 Baud, 8 Bits, even parity, 1 stop bits
GPIO_typeDef *port_uart_tx = GPIOA;
GPIO_typeDef *port_uart_rx = GPIOA;
uint16_t pin_uart_tx = 9;
uint16_t pin_uart_rx = 10;

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
    gpio_set_mode(port_uart_tx, pin_uart_tx, MODER_AF);
    gpio_set_mode(port_uart_rx, pin_uart_rx, MODER_AF);
    gpio_set_alternate_function(port_uart_tx, pin_uart_tx, AF7);
    gpio_set_alternate_function(port_uart_rx, pin_uart_rx, AF7);
    USART2->CR1 = 0;
    USART2->BRR = 1667; //16000000/115200
    USART2->CR1 |= (1 << 0) | (1 << 2) | (1 << 3);

    USART1->CR1 = 0;
    USART1->BRR = 1666; //16000000/115200
    USART1->CR1 |= (1 << 0) | (1 << 2) | (1 << 3);
}

void uart_poll_out(UART_typeDef *uart, unsigned char out_char)
{
    while (1)
    {
        if(uart->ISR & (1<<7))
        break;
    }
    delay_ms(1);
    uart->TDR = out_char;
}

unsigned char uart_poll_in(UART_typeDef *uart)
{
    while ( (uart->ISR & (1 << 5)) != (1 << 5));
    delay_ms(1);
    return (unsigned char) uart->RDR;
}

void uart_tx(UART_typeDef *uart, const uint8_t *buf, size_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        uart_poll_out(uart, buf[i]);
    }
}

void uart_rx(const uint8_t *buf, size_t len)
{
}

void main(void){
    uart_configure();
    while(1)
    {
        unsigned char ch = uart_poll_in(USART1);
        uart_poll_out(USART1, ch);
    }
}