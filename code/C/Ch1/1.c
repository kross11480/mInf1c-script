int main(void){
int *a;
    unsigned int *rcc_ahb2enr = (unsigned int *) 0x40021000 + 0x4c;
    unsigned int *gpio_a_moder = (unsigned int *) 0x48000000;
    unsigned int *gpio_a_odr = (unsigned int *) 0x48000000 + 0x14;

    //initialize gpio
    *rcc_ahb2enr |= 0x1; //Enable Clock for GPIOA
    *gpio_a_moder |= 0x1; //Output Mode for GPIO
    *gpio_a_moder &= ~(1<<1);

    //switch on led 0
    *gpio_a_odr &= ~0x1;
}
