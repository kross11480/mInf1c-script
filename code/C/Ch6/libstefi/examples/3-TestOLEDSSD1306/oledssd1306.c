#include <ctype.h>
#include <libstefi/gpio.h>
#include <libstefi/peripheral.h>
#include <libstefi/uart.h>
#include <libstefi/util.h>
#include <libstefi/systick.h>

#include "stdint.h"
#include "stdio.h"

#include "berry26x32.h"
#include "ssd1306.h"

void test_display() {
    memset(SSD1306_Buffer, 0x00, SSD1306_BUFFER_SIZE);
    ssd1306_update_screen();

    //Write a Character/string

    char *text[] = {
        "A long time ago",
        "  on an OLED ",
        "   display",
        " far far away",
    };

    int y = 0;
    for (uint32_t i = 0 ;i < countof(text); i++) {
        ssd1306_putstring( 5, y, text[i]);
        y+=16;
    }
    ssd1306_update_screen();
    systick_delay_ms(1000);

    struct render_region region =  {
        0,
        0,
        SSD1306_WIDTH,
        SSD1306_HEIGHT,
        };


    // zero the entire display
    systick_restart();
    memset(SSD1306_Buffer, 0xFF, SSD1306_BUFFER_SIZE);
    uint32_t t_in_ms = systick_get_ms();
    printf("memset screen: %d \r\n", t_in_ms);

    systick_restart();
    ssd1306_update_screen();
    t_in_ms = systick_get_ms();
    printf("screen: %d \r\n", t_in_ms);

    //Test Render Region
    struct render_region region1 = {
        48,
        32,
        26,
        32};
    systick_restart();
    ssd1306_render_region(berry26x32, &region1);
    t_in_ms = systick_get_ms();
    printf("render and partial update screen: %d \r\n", t_in_ms);

    systick_delay_ms(1000);


    struct render_region region2 = {
        0,
        0,
        128,
        64};
    memset(SSD1306_Buffer, 0x00, SSD1306_BUFFER_SIZE);

    systick_restart();
    ssd1306_render_region(SSD1306_Buffer, &region2);
    t_in_ms = systick_get_ms();
    printf("render and partial update screen: %d \r\n", t_in_ms);
}

void test_connection() {
    peripheral_gpio_enable(PERIPHERAL_ID_GPIOC);
    gpio_write(C4, HIGH);
    gpio_set_mode(C4, MODER_OUTPUT);
    gpio_write(C4, LOW); //Display On
}

int main(void) {
    uart_configure();

    systick_init();
    systick_start();
    ssd1306_init();
    systick_delay_ms(100); //Wait for OLED to boot

    while(1) {
        test_display();
    }
}