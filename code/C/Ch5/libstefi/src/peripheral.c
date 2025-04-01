
#include "libstefi/peripheral.h"
#include "libstefi/util.h"
#include "../src/internal/rcc_internal.h"

typedef struct {
    volatile uint32_t* rcc_reg;
    uint8_t enable_bit;
} peripheral_dev_t;

static const peripheral_dev_t peripheral_gpio_dev[PERIPHERAL_GPIO_COUNT] = {
    [PERIPHERAL_ID_GPIOA] = {&RCC->AHB2ENR, 0},
    [PERIPHERAL_ID_GPIOB] = {&RCC->AHB2ENR, 1},
    [PERIPHERAL_ID_GPIOC] = {&RCC->AHB2ENR, 2},
};

static const peripheral_dev_t peripheral_tim_dev[PERIPHERAL_TIM_COUNT] = {
    [PERIPHERAL_ID_TIM1] = {&RCC->APB2ENR, 11},
    [PERIPHERAL_ID_TIM2] = {&RCC->APB1ENR, 0},
    [PERIPHERAL_ID_TIM3] = {&RCC->APB1ENR, 1},
    [PERIPHERAL_ID_TIM4] = {&RCC->APB1ENR, 2},
    [PERIPHERAL_ID_TIM5] = {&RCC->APB1ENR, 3},
    [PERIPHERAL_ID_TIM6] = {&RCC->APB1ENR, 4},
    [PERIPHERAL_ID_TIM7] = {&RCC->APB1ENR, 5},
    [PERIPHERAL_ID_TIM8] = {&RCC->APB2ENR, 13},
    [PERIPHERAL_ID_TIM15] = {&RCC->APB2ENR, 16},
    [PERIPHERAL_ID_TIM16] = {&RCC->APB2ENR, 17},
    [PERIPHERAL_ID_TIM17] = {&RCC->APB2ENR, 18},
};

static const peripheral_dev_t peripheral_uart_dev[PERIPHERAL_UART_COUNT] = {
    [PERIPHERAL_ID_UART1] = {&RCC->APB2ENR, 14},
    [PERIPHERAL_ID_UART2] = {&RCC->APB1ENR, 17},
};

void peripheral_gpio_enable(peripheral_id_gpio_t id)
{
    uint8_t pos = peripheral_gpio_dev[id].enable_bit;
    *peripheral_gpio_dev[id].rcc_reg |= BIT(pos);
}

void peripheral_tim_enable(peripheral_id_tim_t id)
{
    uint8_t pos = peripheral_tim_dev[id].enable_bit;
    *peripheral_tim_dev[id].rcc_reg |= BIT(pos);
}

void peripheral_uart_enable(peripheral_id_uart_t id)
{
    uint8_t pos = peripheral_uart_dev[id].enable_bit;
    *peripheral_uart_dev[id].rcc_reg |= BIT(pos);
}


