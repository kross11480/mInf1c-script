#ifndef SSD1306_H
#define SSD1306_H

#include "stdint.h"

#define SSD1306_I2C_ADDR 0x3C
#define I2C_ID 2
#define SCL B10
#define SDA B11
#define DISPLAY_SWITCH_PIN B5

#define SSD1306_HEIGHT          64
#define SSD1306_WIDTH           128
#define SSD1306_BUFFER_SIZE   SSD1306_WIDTH * SSD1306_HEIGHT / 8

extern uint8_t SSD1306_Buffer[];

struct render_region {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
};

void test_init();

// Public API
void ssd1306_init(void);
void ssd1306_update_screen(void);
void ssd1306_clear_screen(void);
void ssd1306_render_region(uint8_t *buf, struct render_region *region);
void ssd1306_set_pixel(int x, int y, int on);
void ssd1306_putchar(uint32_t x, uint32_t y, uint8_t ch);
void ssd1306_putstring(uint32_t x, uint32_t y, char *str);

#endif