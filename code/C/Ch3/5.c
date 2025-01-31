#include <stdio.h>
#include <string.h>
#include <assert.h>

//Task: use assert to test a simple function
// Use it to test a simple add function
//Note: #x converts a macro argument x into a string, (x) is evaluate x
//Note: output from buffer shown only until \r\n
//Note: ? ternary operator
//Note: Write strrchr: pointer to last occurence of character in string

#include "uart.h"


#define TEXTIFY(x) #x
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1: __FILE__ )
#define STEFI_ASSERT(expr) do {if(!(expr)) {printf("Failed:%s, %d: %s\r\n", __FILENAME__, __LINE__, TEXTIFY(expr)); return; } } while(0)

int add(int a, int b)
{
    return a+b;
}

void test_add()
{
    STEFI_ASSERT(7 == add(3,4));
}

void test_gpio()
{
    STEFI_ASSERT((GPIOB->ODR & (1<<8)) == LOW);
}
void gpio_init()
{
    RCC->AHB2ENR |= 1 << 1; //Clock to Port B
    //User LED on Port B8 (Default)
    gpio_set_mode(GPIOB, 8, MODER_OUTPUT);
    gpio_write(GPIOB, 8, HIGH);
}

void main(){
    uart_configure();
    printf("\x1b[34m" "UNIT TESTS \x1b[0m \r\n");
    test_add();
    gpio_init();
    test_gpio();
}
