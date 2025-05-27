#pragma once
#include <stdint.h>

typedef struct {
    volatile uint32_t REGS_NOTNEEDEDNOW[19];
    volatile uint32_t AHB2ENR;  // AHB2 peripheral clock enable register
    volatile uint32_t AHB3ENR;  // AHB3 peripheral clock enable register
    volatile uint32_t RESERVED;
    volatile uint32_t APB1ENR1;  // APB1 peripheral clock enable register
    volatile uint32_t APB1ENR2;
    volatile uint32_t APB2ENR;
} RCC_typeDef;

#define RCC ((RCC_typeDef *) 0x40021000) //Operator precedence remove ()