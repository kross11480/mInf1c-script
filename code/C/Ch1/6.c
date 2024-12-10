/*replace delay with Systick Timer*/
// 1. Datasheet: pg 246 Programming Manual
// 2. Init
// 3. Function

//
typedef unsigned int uint32_t;

typedef struct {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
} SysTick_t;

typedef struct {
    volatile uint32_t MODER;    // GPIO mode register
    volatile uint32_t OTYPER;   // GPIO output type register
    volatile uint32_t OSPEEDR;  // GPIO output speed register
    volatile uint32_t PUPDR;    // GPIO pull-up/pull-down register
    volatile uint32_t IDR;      // GPIO input data register
    volatile uint32_t ODR;      // GPIO output data register
    volatile uint32_t BSRR;     // GPIO bit set/reset register
    volatile uint32_t LCKR;     // GPIO lock register
    volatile uint32_t AFR[2];   // GPIO alternate function registers
} GPIO;

typedef struct {
    uint32_t REGS_NOTNEEDEDNOW[19];
    uint32_t AHB2ENR;  // AHB2 peripheral clock enable register
} RCC_typeDef;

#define SysTick ((SysTick_t *) 0xE000E010)

/* Base Address of Peripheral */
GPIO *GPIOA = (GPIO *) 0x48000000;
RCC_typeDef *RCC = (RCC_typeDef *) 0x40021000;

void SysTick_Config(){
    SysTick->CTRL |= 0x1;
    SysTick->LOAD = 2000000;
}

void setup(){
    //initialize gpio
    RCC->AHB2ENR |= 0x1; //Enable Clock for GPIOA
    GPIOA->MODER &= ~(0xC);
    GPIOA->MODER |= (0x4);

    SysTick_Config();
}


int main(){
    setup();
    while(1){
        if(SysTick->VAL == 0)
            GPIOA->ODR ^= 0x2;
    }
}
