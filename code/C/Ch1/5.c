//Compiler Explorer: https://gcc.godbolt.org/z/85db6GYn9
int main(void){
    unsigned int *gpio_a_odr = (unsigned int *) 0x48000014;
    //switch on led 0
    *gpio_a_odr ^= 0x1;
}
/*
main:
        mov     r0, #20
        orr     r0, r0, #1207959552
        ldr     r1, [r0]
        eor     r1, r1, #1
        str     r1, [r0]
        bx      lr
 */