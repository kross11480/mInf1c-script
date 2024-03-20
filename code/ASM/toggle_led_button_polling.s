.syntax unified
.cpu cortex-m4
.thumb

#led 3 is on GPIO Port C7 on AHB2Bus
#button 0 is on GPIO Port BO
# rcc base 0x40021000, rcc clock enable offset is 0x4C
# gpioc base is 0x48000800, offset odr:0x14 , mode:0x00,
# gpiob base is 0x48000400, offset idr:0x10, mode:0x00 , pullup:0x0C
.equ gpio_clock_address, 0x4002104C
.equ gpoic_out_address, 0x48000814
.equ gpioc_mode_address, 0x48000800
.equ gpiob_mode_address, 0x48000400
.equ gpiob_in_address, 0x48000410
.equ gpiob_pullup_address, 0x4800040C
.equ delay_toggle, 0x10000 @calculate value
.equ delay_bounce, 0x10000

.word 0
.word _start + 1
.global _start
_start:
#initialize gpio and rcc
# intialize rcc, set bit 2 and bit 1 to 1
ldr r0, =gpio_clock_address
ldr r1, [r0]
orr r1, 0x6
str r1, [r0]

#initialize gpioc
#mode output is 01, set bit 15 to 0, reset value 0xffffffff
ldr r0, =gpioc_mode_address
ldr r1, [r0]
and r1, 0xFFFF7FFF
str r1, [r0]

#switch of led on reset
ldr r0, =gpoic_out_address
ldr r1, [r0]
orr r1, 0x80 @xor bit 7
str r1, [r0]


#initialize gpiob
#mode input is 00, reset value 0xFFFFFEBF, set bit 1 and 0 to 0
ldr r0, =gpiob_mode_address
ldr r1, [r0]
and r1, 0xFFFFFFFC
str r1, [r0]

#pullup is 01, reset value is 0x00000100, set bit 0 to 1
ldr r0, =gpiob_pullup_address
ldr r1, [r0]
orr r1, 0x1
str r1, [r0]

#initialize app state and button state
mov r2, 0x1 @led state
mov r3, 0x1 @previous button state
mov r5, 0x1 @current button state

#toggle on button press
forever_loop:
bl read_button
cmp r2, 0x0
bne forever_loop
bl toggle_led
b forever_loop

read_button:
ldr r0, =gpiob_in_address
ldr r1, [r0]
and r5, r1, 0x1
cmp r3, 0x0
beq return_loop
cmp r5, 0x0
beq update_state
bl delay
return_loop:
ldr r1, [r0]
and r5, r1, 0x1
mov r3, r5
bx lr

update_state:
eor r2, r2, 0x1
bx lr

toggle_led:
ldr r0, =gpoic_out_address
ldr r1, [r0]
eor r1, 0x80 @xor bit 7
str r1, [r0]
bx lr

delay:
movs r0, #0
ldr r1, =delay_toggle
loop:
    add r0, r0, 1
    cmp r0, r1
    bne loop
    bx lr


