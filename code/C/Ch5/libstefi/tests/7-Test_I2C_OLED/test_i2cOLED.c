#include <ctype.h>
#include <libstefi/uart.h>
#include <libstefi/util.h>
#include <libstefi/systick.h>

#include "stdint.h"
#include "stdio.h"
#include "berry26_32.h"

#include "ssd1306.h"


int main(void) {
    systick_init();
    systick_start();

    ssd1306_init();

    // Clear screen
    memset(SSD1306_Buffer, 0x00, sizeof(SSD1306_Buffer));
    //Update Screen
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
    //systick_delay_ms(1000);

    // struct render_region region =  {
    //     0,
    //     0,
    //     SSD1306_WIDTH,
    //     SSD1306_HEIGHT,
    //     };
    //
    //
    // // zero the entire display
    // uint8_t buf[SSD1306_WIDTH*SSD1306_HEIGHT/8];
    // memset(buf, 0xFF, countof(buf));
    // ssd1306_render_region(buf, &region);
    //
    // // memset(SSD1306_Buffer, 0xFF, SSD1306_BUFFER_SIZE);
    // // ssd1306_update_screen();
    // struct render_region region1 = {
    // 48,
    // 32,
    // 26,
    // 32};
    // ssd1306_render_region(berry26x32, &region1);
    while(1) {
    }
}