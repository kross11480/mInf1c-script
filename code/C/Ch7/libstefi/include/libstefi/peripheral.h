#pragma once

/**********************************************************************/
/* RCC (Reset Clock Control) Hardware Abstraction layer               */
/**********************************************************************/
enum peripheral_gpio {
    PERIPHERAL_GPIOA,
    PERIPHERAL_GPIOB,
    PERIPHERAL_GPIOC,
    PERIPHERAL_GPIO_COUNT
};

enum peripheral_tim {
    PERIPHERAL_TIM1,
    PERIPHERAL_TIM2,
    PERIPHERAL_TIM3,
    PERIPHERAL_TIM4,
    PERIPHERAL_TIM5,
    PERIPHERAL_TIM6,
    PERIPHERAL_TIM7,
    PERIPHERAL_TIM8,
    PERIPHERAL_TIM15 = 14,
    PERIPHERAL_TIM16,
    PERIPHERAL_TIM17,
    PERIPHERAL_TIM_COUNT
};

enum peripheral_uart {
    PERIPHERAL_UART1,
    PERIPHERAL_UART2,
    PERIPHERAL_UART_COUNT
};

enum peripheral_i2c {
    PERIPHERAL_I2C1,
    PERIPHERAL_I2C2,
    PERIPHERAL_I2C3,
    PERIPHERAL_I2C_COUNT
};

enum peripheral_spi {
    PERIPHERAL_SPI1,
    PERIPHERAL_SPI2,
    PERIPHERAL_SPI3,
    PERIPHERAL_SPI_COUNT
};

enum peripheral_adc {
    PERIPHERAL_ADC1,
    PERIPHERAL_ADC2,
    PERIPHERAL_ADC3,
    PERIPHERAL_ADC_COUNT
};

typedef enum peripheral_gpio peripheral_gpio_t;
typedef enum peripheral_tim peripheral_tim_t;
typedef enum peripheral_uart peripheral_uart_t;
typedef enum peripheral_i2c peripheral_i2c_t;
typedef enum peripheral_spi peripheral_spi_t;
typedef enum peripheral_adc peripheral_adc_t;

/**
 * @brief Enable clock for specified GPIO peripheral
 */
void peripheral_gpio_enable(peripheral_gpio_t);

/**
 * @brief Enable clock for specified Timer peripheral
 */
void peripheral_tim_enable(peripheral_tim_t);

/**
 * @brief Enable clock for specified UART peripheral
 */
void peripheral_uart_enable(peripheral_uart_t);
void peripheral_i2c_enable(peripheral_i2c_t id);
void peripheral_spi_enable(peripheral_spi_t id);
void peripheral_adc_enable(peripheral_adc_t id);
void peripheral_exti_enable();
void peripheral_rng_enable();