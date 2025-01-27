#include "hal.h"
#include "stddef.h"

//Task: Uart, Character Output @115200 Baud, 8 Bits, none parity, 1 stop bits, UTF-8
//Note: New board needs ST-Link Firmware Upgrade
//Note: Use Macros for Baud rate
//Note:
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
    if (af < 8)
    {
        gpio->AFR[0] |= (af << (4*pin));
    }
    else
    {
        gpio->AFR[1] |= (af << (4*pin));
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
void uart_poll_out(unsigned char out_char);
void uart_tx(const uint8_t *buf, size_t len);

#define USART2 ((UART_typeDef *) 0x40004400)

void uart_configure(){
    //UM2397: USART2 (PA2/PA3) connected to STLINK-V3E Virtual COM port.
    RCC->APB1ENR |= (1 << 17); //switch on UART2
    RCC->AHB2ENR |= (1 << 0);

    gpio_set_alternate_function(port_uart_tx, pin_uart_tx, AF7);
    gpio_set_alternate_function(port_uart_rx, pin_uart_rx, AF7);
    gpio_set_mode(port_uart_tx, pin_uart_tx, MODER_AF);
    gpio_set_mode(port_uart_rx, pin_uart_rx, MODER_AF);

    USART2->CR1 = 0;
    USART2->BRR = 16000000/115200; //16000000/115200
    USART2->CR1 |= (1 << 0) | (1 << 3) | (1 << 2);
}

void uart_poll_out(unsigned char out_char)
{
    while ((USART2->ISR & (1<<7)) == 0) delay_ms(1);
    USART2->TDR = out_char;
}

void uart_tx(const uint8_t *buf, size_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        uart_poll_out(buf[i]);
    }
}

void main(void){
    const uint8_t wordsBuffer[] = {
        'H',
        'a',
        'l',
        'l',
        'o',
        ' ',
        'W',
        'e',
        'l',
        't',
        '!',
        '!',
        '\r',
        '\n',
    };

    uart_configure();
    uart_tx(wordsBuffer, sizeof(wordsBuffer));
    uart_tx(wordsBuffer, sizeof(wordsBuffer));
}