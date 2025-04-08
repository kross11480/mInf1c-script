/**********************************************************************/
/* RCC (Reset Clock Control) Hardware Abstraction layer               */
/**********************************************************************/
typedef enum peripheral_id_gpio peripheral_id_gpio_t;
typedef enum peripheral_id_tim peripheral_id_tim_t;
typedef enum peripheral_id_uart peripheral_id_uart_t;

void peripheral_gpio_enable(peripheral_id_gpio_t);
void peripheral_tim_enable(peripheral_id_tim_t);
void peripheral_uart_enable(peripheral_id_uart_t);
void peripheral_exti_enable();

enum peripheral_id_gpio {
    PERIPHERAL_ID_GPIOA,
    PERIPHERAL_ID_GPIOB,
    PERIPHERAL_ID_GPIOC,
    PERIPHERAL_GPIO_COUNT
};

enum peripheral_id_tim {
    PERIPHERAL_ID_TIM1,
    PERIPHERAL_ID_TIM2,
    PERIPHERAL_ID_TIM3,
    PERIPHERAL_ID_TIM4,
    PERIPHERAL_ID_TIM5,
    PERIPHERAL_ID_TIM6,
    PERIPHERAL_ID_TIM7,
    PERIPHERAL_ID_TIM8,
    PERIPHERAL_ID_TIM15,
    PERIPHERAL_ID_TIM16,
    PERIPHERAL_ID_TIM17,
    PERIPHERAL_TIM_COUNT
};

enum peripheral_id_uart {
    PERIPHERAL_ID_UART1,
    PERIPHERAL_ID_UART2,
    PERIPHERAL_UART_COUNT
};