.syntax unified
.cpu cortex-m4
.thumb

.equ gpio_clock_address, 0x4002104C
.equ led_address, 0x48000014
.equ gpio_mode_address, 0x48000000
.equ delay_count, 0x10000

.word 0
.word _start + 1
.global _start
_start:
#Initialize Clock
    ldr r0, =0x00000001
    ldr r1, =gpio_clock_address
    str r0, [r1]

#Initialize LED 0
#- LEDs: GPIOC->MODER = (GPIOC->MODER & 0xFFFF00FF) | 0x00004000;
    ldr r1, =gpio_mode_address
    ldr r0, [r1]
    and r0, 0xFFFFFFFC
    orr r0, 0x00000001
    str r0, [r1]

toggle:
#Toggle LED
    ldr r1, =led_address
    ldr r0, [r1]
    eor r0, 0x0000001
    str r0, [r1]
    bl delay
    b toggle

delay:
    movs    r6, #0
    ldr     r7, =0x100000
.L1:
    adds    r6, r6, #1
    cmp     r6, r7
    bne     .L1
    bx      lr
