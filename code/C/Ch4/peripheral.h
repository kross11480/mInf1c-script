/**********************************************************************/
/* RCC (Reset Clock Control) Hardware Abstraction layer               */
/**********************************************************************/
#include <stdint.h>

typedef struct {
    uint32_t REGS_NOTNEEDEDNOW[19];
    uint32_t AHB2ENR;  // AHB2 peripheral clock enable register
    uint32_t AHB3ENR;  // AHB3 peripheral clock enable register
    uint32_t RESERVED;
    uint32_t APB1ENR;  // APB1 peripheral clock enable register
    uint32_t APB1ENR2;
    uint32_t APB2ENR;
} RCC_typeDef;

#define RCC ((RCC_typeDef *) 0x40021000) //Operator precedence remove ()