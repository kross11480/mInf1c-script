//Task: Traffic Light Implementation
//Description: Vehicle traffic light: Red (LED0, A0), yellow (LED1) and green (LED2)
// Pedestrian traffic light: Blue LED3) flashing for “Pedestrians may walk”
//The vehicle traffic light is normally green.
//10 s after pressing the S0 button, the vehicle traffic light switches to yellow, 1 s later to red.
//1 s later, the blue LED should flash for 15 s at 1 Hz.
//The blue LED should then go out and the traffic light should switch back to green
// Optional: (or first to red-yellow and then to green after 1 s).

#include <stdint.h>
#include <stdio.h>
#include "gpio.h"
#include "timer.h"
#include "uart.h"

typedef enum state{
    GREEN,
    RED,
    YELLOW,
    YELLOWRED,
    BLUERED,
} state_t;

#define DELAY_RED 2000
#define DELAY_YELLOW 2000
#define DELAY_GREEN 5000
#define DELAY_YELLOWRED 2000
#define DELAY_BLINK_1HZ 500
#define DELAY_BLUEBLINK_NUM 20

void main()
{
    unsigned int current_state = GREEN;
    uint32_t led_green = A2;
    uint32_t led_red = A0;
    uint32_t led_yellow = A1;
    uint32_t led_blue = A3;
    uint32_t button_S0 = B0;

    RCC->AHB2ENR |= (1 << 0);
    RCC->AHB2ENR |= (1 << 1);

    //Switch off all leds
    gpio_write(led_red, HIGH);
    gpio_write(led_yellow, HIGH);
    gpio_write(led_green, HIGH);
    gpio_write(led_blue, HIGH);

    //initialize to output
    gpio_set_mode(led_red, MODER_OUTPUT);
    gpio_set_mode(led_yellow, MODER_OUTPUT);
    gpio_set_mode(led_green, MODER_OUTPUT);
    gpio_set_mode(led_blue, MODER_OUTPUT);
    gpio_set_mode(button_S0, MODER_INPUT);

    //initialize internal pullup
    gpio_set_pupd(button_S0, PULL_UP);

    timer_init();
    timer_start();

    uart_configure();
    char buf0[10], buf1[50], buf2[100];
    sscanf("led blink 500", "%9s %49s %99[^\r\n]", buf0, buf1, buf2);
    printf("Hello World!! \r\n");
    printf("%s \r\n", buf0);
    while(1){
        switch(current_state)
        {
        case GREEN:
            gpio_write(led_red, HIGH);
            gpio_write(led_yellow, HIGH);
            gpio_write(led_green, LOW);
            if(gpio_read(button_S0) == LOW)
            {
                soft_delay_ms(DELAY_GREEN);
                current_state = YELLOW;
            }
            break;
        case YELLOW:
            gpio_write(led_green, HIGH);
            gpio_write(led_yellow, LOW);
            soft_delay_ms(DELAY_YELLOW);
            current_state = RED;
            break;
        case RED:
            gpio_write(led_yellow, HIGH);
            gpio_write(led_red, LOW);
            soft_delay_ms(DELAY_RED);
            current_state = BLUERED;
            break;
        case BLUERED:
            gpio_write(led_blue, LOW);
            gpio_write(led_red, LOW);
            for(uint32_t i = 0; i < DELAY_BLUEBLINK_NUM; i++)
            {
                soft_delay_ms(DELAY_BLINK_1HZ);
                gpio_toggle(led_blue);
            }
            current_state = YELLOWRED;
            break;
        case YELLOWRED:
            gpio_write(led_blue, HIGH);
            gpio_write(led_red, LOW);
            gpio_write(led_yellow, LOW);
            soft_delay_ms(DELAY_YELLOWRED);
            current_state = GREEN;
            break;
        default:
            current_state = GREEN;
            break;
        }
    }
}