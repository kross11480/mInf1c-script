#include "ssd1306.h"

#include <ctype.h>
#include <libstefi/systick.h>
#include <libstefi/util.h>

#include "font.h"
#include "libstefi/i2c.h"

static void ssd1306_write_cmd(uint8_t byte) {
    i2c_writeto_reg(I2C_ID, SSD1306_I2C_ADDR, 0x80, &byte, 1);
}

static void ssd1306_write_data(uint8_t* buffer, uint32_t buff_size) {
    i2c_writeto_reg(I2C_ID, SSD1306_I2C_ADDR, 0x40, buffer, buff_size);
}

static void ssd1306_write_cmd_list(uint8_t *buf, uint32_t num) {
    for (int i=0;i<num;i++)
        ssd1306_write_cmd(buf[i]);
}

/* update display with actual fb */
void ssd1306_update_screen(void) {
    for(uint8_t i = 0; i < SSD1306_HEIGHT/8; i++) {
        ssd1306_write_cmd(0xB0 + i); // Set the current RAM page address.
        ssd1306_write_cmd(0x00);
        ssd1306_write_cmd(0x10);
        ssd1306_write_data(&SSD1306_Buffer[SSD1306_WIDTH*i],SSD1306_WIDTH);
    }
}

void ssd1306_render_region(uint8_t *buf, struct render_region *region) {
    uint32_t start_page = (region->y / 8);
    uint32_t end_page = ((region->y + region->height -1) / 8);
    uint32_t end_col = (region->x + region->width - 1);
    // update a portion of the display with a render area
    uint8_t cmds[] = {
        0x21,
        region->x,
        end_col,
        0x22,
        start_page,
        end_page,
    };

    ssd1306_write_cmd_list(cmds, countof(cmds));

    uint32_t buflen = (end_col - region->x + 1) * (end_page - start_page + 1);
    ssd1306_write_data(buf, buflen);
}

void ssd1306_set_pixel(int x, int y, int on) {
    if (x < 0 || x >= SSD1306_WIDTH || y < 0 || y >= SSD1306_HEIGHT) return;
    uint32_t page = y / 8;
    uint32_t bit = y % 8;
    if(on) {
        SSD1306_Buffer[x + SSD1306_WIDTH*page] |= 1 << bit;
    } else {
        SSD1306_Buffer[x + SSD1306_WIDTH*page] &= ~(1 << bit);
    }
}

void ssd1306_putchar(uint32_t x, uint32_t y, uint8_t ch) {
    y = y/8;
    uint32_t font_idx = (toupper(ch) + 1 - 'A')*8;
    uint32_t frame_buffer_idx = y*128 + x;

    for(uint32_t i = 0; i < 8; i++) {
        SSD1306_Buffer[frame_buffer_idx++] = font[font_idx];
        font_idx++;
    }
}

void ssd1306_putstring(uint32_t x, uint32_t y, char *str) {
    while(*str) {
        ssd1306_putchar(x, y, *str++);
        x+=8;
    }
}

void ssd1306_init() {
    i2c_init(I2C_ID, SCL, SDA);
    gpio_write(DISPLAY_SWITCH_PIN, HIGH);
    gpio_set_mode(DISPLAY_SWITCH_PIN, MODER_OUTPUT);
    gpio_write(DISPLAY_SWITCH_PIN, LOW); //Display On
    systick_delay_ms(100);

    uint8_t cmds[] = {
        0xAE, 0x20, 0x00, 0xB0, 0xC8,
        0x00, 0x10, 0x40,
        0x81, 0xFF,
        0xA1, 0xA6,
        0xA8, 0x3F,
        0xA4,
        0xD3, 0x00,
        0xD5, 0xF0,
        0xD9, 0x22,
        0xDA, 0x12,
        0xDB, 0x20,
        0x8D, 0x14,
        0xAF
    };

    //uint8_t cmds[] = {0xAE, 0x20, 0x00, 0xB0, 0xC8};
    ssd1306_write_cmd_list(cmds, countof(cmds));

    // ssd1306_write_cmd(0x00); //---set low column address
    // ssd1306_write_cmd(0x10); //---set high column address
    // ssd1306_write_cmd(0x40); //--set start line address - CHECK
    //
    // //Set Contrast
    // ssd1306_write_cmd(0X81);
    // ssd1306_write_cmd(0xFF);
    //
    // ssd1306_write_cmd(0xA1); //--set segment re-map 0 to 127 -
    // ssd1306_write_cmd(0xA6); //--set normal color
    //
    // ssd1306_write_cmd(0xA8); //--set multiplex ratio(1 to 64) -
    // ssd1306_write_cmd(0x3F); //64 lines of height
    //
    // ssd1306_write_cmd(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    //
    // ssd1306_write_cmd(0xD3); //-set display offset -
    // ssd1306_write_cmd(0x00); //-not offset
    //
    // ssd1306_write_cmd(0xD5); //--set display clock divide ratio/oscillator frequency
    // ssd1306_write_cmd(0xF0); //--set divide ratio
    //
    // ssd1306_write_cmd(0xD9); //--set pre-charge period
    // ssd1306_write_cmd(0x22); //
    //
    // ssd1306_write_cmd(0xDA); //--set com pins hardware configuration -
    // ssd1306_write_cmd(0x12);
    //
    // ssd1306_write_cmd(0xDB); //--set vcomh
    // ssd1306_write_cmd(0x20); //0x20,0.77xVcc
    //
    // ssd1306_write_cmd(0x8D); //--set DC-DC enable
    // ssd1306_write_cmd(0x14); //
    //
    // ssd1306_write_cmd(0xAF); //--turn on SSD1306 panel

}

// Clear screen (set buffer to 0)
void ssd1306_clear_screen(void) {
    ssd1306_write_cmd(0xAE); // Display off
    ssd1306_write_cmd(0x20); // Set Memory Addressing Mode
    ssd1306_write_cmd(0x00); // Horizontal Addressing Mode
    memset(SSD1306_Buffer, 0x00, SSD1306_BUFFER_SIZE);
    ssd1306_write_cmd(0xAF);

}
