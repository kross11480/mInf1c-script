// Task: Switch on LED connected to GPIO (PORT A, Pin 1)
// Access memory mapped peripheral register with pointers

#define GPIOA_BASE 0x48000000

#define GPIOA_MODER *(volatile unsigned int *)(GPIOA_BASE + 0x00)
#define GPIOA_ODR *(volatile unsigned int *)(GPIOA_BASE + 0x14)

int main(void){

    volatile unsigned int *RCC_AHB2ENR = (volatile unsigned int *)(0x40021000 + 0x4C);
    unsigned int pin = 1; //LED connected to PA1

    *RCC_AHB2ENR |= 0x1; //Enable GPIOA Clock
    GPIOA_MODER &= ~(3<<(2*pin)); // Set Port
    GPIOA_MODER |= (0x1<<(2*pin));

    GPIOA_ODR &= ~(0x1<<pin);

    return 0;
}
