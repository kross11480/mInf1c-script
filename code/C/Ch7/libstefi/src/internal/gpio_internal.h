#pragma once

#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;    // 0x00: mode register
    volatile uint32_t OTYPER;   // 0x04: GPIO output type register
    volatile uint32_t OSPEEDR;  // 0x08: GPIO output speed register
    volatile uint32_t PUPDR;    // 0x0C: GPIO pull-up/pull-down register
    volatile uint32_t IDR;      // 0x10: GPIO input data register
    volatile uint32_t ODR;      // 0x14: GPIO output data register
    volatile uint32_t BSRR;     // 0x18: GPIO bit set/reset register
    volatile uint32_t LCKR;     // 0x1C: GPIO lock register
    volatile uint32_t AFR[2];   // 0x20: GPIO alternate function registers
    volatile uint32_t BRR;         /*!< GPIO Bit Reset register,               Address offset: 0x28      */
    volatile uint32_t ASCR;        /*!< GPIO analog switch control register,   Address offset: 0x2C     */


} GPIO_typeDef;

#define GPIO_BASE (0x48000000)
#define GPIO_PORTOFFSET (0x400)

//For compatibility, low level test code
#define GPIOA ((GPIO_typeDef *) 0x48000000)
#define GPIOB ((GPIO_typeDef *) 0x48000400)
#define GPIOC ((GPIO_typeDef *) 0x48000800)

typedef struct
{
    volatile uint32_t IMR1;        /*!< EXTI Interrupt mask register 1,             Address offset: 0x00 */
    volatile uint32_t EMR1;        /*!< EXTI Event mask register 1,                 Address offset: 0x04 */
    volatile uint32_t RTSR1;       /*!< EXTI Rising trigger selection register 1,   Address offset: 0x08 */
    volatile uint32_t FTSR1;       /*!< EXTI Falling trigger selection register 1,  Address offset: 0x0C */
    volatile uint32_t SWIER1;      /*!< EXTI Software interrupt event register 1,   Address offset: 0x10 */
    volatile uint32_t PR1;         /*!< EXTI Pending register 1,                    Address offset: 0x14 */
    uint32_t      RESERVED1;   /*!< Reserved, 0x18                                                   */
    uint32_t      RESERVED2;   /*!< Reserved, 0x1C                                                   */
    volatile uint32_t IMR2;        /*!< EXTI Interrupt mask register 2,             Address offset: 0x20 */
    volatile uint32_t EMR2;        /*!< EXTI Event mask register 2,                 Address offset: 0x24 */
    volatile uint32_t RTSR2;       /*!< EXTI Rising trigger selection register 2,   Address offset: 0x28 */
    volatile uint32_t FTSR2;       /*!< EXTI Falling trigger selection register 2,  Address offset: 0x2C */
    volatile uint32_t SWIER2;      /*!< EXTI Software interrupt event register 2,   Address offset: 0x30 */
    volatile uint32_t PR2;         /*!< EXTI Pending register 2,                    Address offset: 0x34 */
} EXTI_typeDef;

#define EXTI ((EXTI_typeDef *) 0x40010400)
#define NUM_EXTIINTERRUPTS 16

typedef struct
{
    volatile uint32_t MEMRMP;      /*!< SYSCFG memory remap register,                        Address offset: 0x00      */
    volatile uint32_t CFGR1;       /*!< SYSCFG configuration register 1,                     Address offset: 0x04      */
    volatile uint32_t EXTICR[4];   /*!< SYSCFG external interrupt configuration registers,   Address offset: 0x08-0x14 */
    volatile uint32_t SCSR;        /*!< SYSCFG CCMSRAM control and status register,          Address offset: 0x18      */
    volatile uint32_t CFGR2;       /*!< SYSCFG configuration register 2,                     Address offset: 0x1C      */
    volatile uint32_t SWPR;        /*!< SYSCFG CCMSRAM write protection register,            Address offset: 0x20      */
    volatile uint32_t SKR;         /*!< SYSCFG CCMSRAM Key Register,                         Address offset: 0x24      */
} SYSCFG_typeDef;

#define SYSCFG ((SYSCFG_typeDef *) 0x40010000)