.syntax unified
@.cpu cortex-m4
@.thumb

.word 0
.word _start + 1
.global _start
_start:
mov r0,#7
mov r1,#8
adds r1, r0, #1
b .