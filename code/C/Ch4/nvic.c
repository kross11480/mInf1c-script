#include <stdint.h>
#include "util.h"
#include "nvic.h"
/** NVIC register map type. */
typedef struct {
    uint32_t ISER[8];      /**< Interrupt Set Enable Registers */
    uint32_t RESERVED0[24];
    uint32_t ICER[8];      /**< Interrupt Clear Enable Registers */
    uint32_t RESERVED1[24];
    uint32_t ISPR[8];      /**< Interrupt Set Pending Registers */
    uint32_t RESERVED2[24];
    uint32_t ICPR[8];      /**< Interrupt Clear Pending Registers */
    uint32_t RESERVED3[24];
    uint32_t IABR[8];      /**< Interrupt Active bit Registers */
    uint32_t RESERVED5[644];
    uint32_t STIR;         /**< Software Trigger Interrupt Registers */
} NVIC_typeDef;

#define NVIC_BASE ((NVIC_typeDef *) 0xE000E100)

void NVIC_EnableIRQ(nvic_source_t irq_num){
    NVIC_BASE->ISER[irq_num/32] |= BIT(irq_num%32);
}