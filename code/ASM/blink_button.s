.syntax unified
.cpu cortex-m4
.thumb

.word 0x20004000
.word reset
#.space 0xe4

reset:
#Initialize Clock for GPIOC, GPIOB, GPIOA
    ldr r0, =0x00000006
    ldr r1, =0x4002104C
    str r0, [r1]

#Initialize LED 0,1,2,3
#- switch all LED off: bit value 1 is LED OFF, bit value 0 is LED ON
#- OFF/ON: GPIOC -> ODR |= (1<<7); GPIOC->ODR &= ~( 1 << i );
    ldr r1, =0x48000814
    ldr r0, [r1]
    orr r0, 0x00000F0
    str r0, [r1]

#- LEDs: GPIOC->MODER = (GPIOC->MODER & 0xFFFF00FF) | 0x00005500;
    ldr r1, =0x48000800
    ldr r0, [r1]
    and r0, 0xFFFF00FF
    orr r0, 0x00005500
    str r0, [r1]

# Initialize button 0,1,2,3
# set MODER  to input:
#GPIOB->MODER &= 0xFFFFFF00;
    ldr r1, =0x48000400
    ldr r0, [r1]
    and r0, 0xFFFFFF00
    str r0, [r1]

#set PUPDR : GPIOB->PUPDR = (GPIOB->PUPDR & 0xFFFFFF00) | 0b01010101;
    ldr r1, =0x4800040C
    ldr r0, [r1]
    and r0, 0xFFFFFF00
    orr r0, 0x00000055
    str r0, [r1]

mov r4, 0x1 @prestate
mov r5, 0x1 @state

read_button:
    ldr r1, =0x48000410
    ldr r0, [r1] @state
    ands r5,r0, 0x1
    bne update_state
    ands r4, 0x1
    beq update_state
    bl delay
    ldr r0, [r1] @state
    ands r0, 0x1
    bne update_state
    #Toggle LED
    ldr r1, =0x48000814
    ldr r0, [r1]
    eor r0, 0x00000F0
    str r0, [r1]

update_state:
    mov r4, r5
    b read_button

b . @ Never ending loop

delay:
    MOVS    r6, #0
    LDR     r7, =0x10000
.L1:
    ADDS    r6, r6, #1
    CMP     r6, r7
    BNE     .L1
    BX      lr