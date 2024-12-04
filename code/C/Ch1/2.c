/* typedef create new name for existing data type */
typedef unsigned int uint32_t;

/* struct is user defined datatype containing several named variables */
typedef struct gpio{
    uint32_t MODER;
} GPIO;


int main(void){
    uint32_t *rcc_ahb2enr = (uint32_t *) 0x4002104c;
    uint32_t *gpio_a_odr = (uint32_t *) 0x48000014;

    /* gpioA is a pointer to GPIO Struct and it points to based address of GPIO Peripheral */
    GPIO *gpioA = (GPIO *) 0x48000000;

    //initialize gpio
    *rcc_ahb2enr |= 0x1; //Enable Clock for GPIOA

    /* What is -> opearator, access to memnber */
    (*gpioA).MODER &= ~(0x3);
    //gpioA->MODER &= ~(0x3);


    gpioA->MODER |= (0x1);

    //switch on led 0
    *gpio_a_odr &= ~0x1;

    while(1){
    }
}