/* */
.syntax unified
.cpu cortex-m4
.thumb

.equ gpio_clock_address, 0x4002104C
.equ ledC_address, 0x48000814
.equ gpio_mode_address, 0x48000800
.equ delay_count, 0x10000

.word 0
.word _start + 1
.global _start
_start:
#Initialize Clock for GPIOC
    ldr r0, =0x00000004
    ldr r1, =gpio_clock_address
    str r0, [r1]

#Initialize LED 3
#- switch LED 3(Port GPIO C7) off: bit value 1 is LED OFF, bit value 0 is LED ON
#- OFF/ON: GPIOC -> ODR |= (1<<7); GPIOC->ODR &= ~( 1 << 7 );
    ldr r1, =ledC_address
    ldr r0, [r1]
    orr r0, 0x0000080
    str r0, [r1]

#- LEDs: GPIOC->MODER = (GPIOC->MODER & 0xFFFF00FF) | 0x00004000;
    ldr r1, =gpio_mode_address
    ldr r0, [r1]
    and r0, 0xFFFF3FFF
    orr r0, 0x00004000
    str r0, [r1]

toggle:
#Toggle LED
    ldr r1, =ledC_address
    ldr r0, [r1]
    eor r0, 0x00000F0
    str r0, [r1]
    bl delay

delay:
    movs    r6, #0
    ldr     r7, =delay_count
.L1:
    adds    r6, r6, #1
    cmp     r6, r7
    bne     .L1
    bx      lr
