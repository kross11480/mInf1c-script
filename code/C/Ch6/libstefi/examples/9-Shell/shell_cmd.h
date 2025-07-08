#pragma once
#include <led.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_memview(const uint32_t *buf, uint32_t len) {

    const uint32_t *p = (const uint32_t *) buf;

    for (uint32_t i = 0; i < len; i++) {
        if ((i % 8) == 0) {
            if (i > 0) {
                printf("\n");
            }
            printf("%8p   |", p+i);
        }
        printf("%8x",(unsigned int) p[i]);
        printf(" ");
    }
    printf("\n");
}

static int cmd_help(int argc, char *argv[]) {

    printf("commands:\r\n");
    printf("help [command]\r\n");
    printf("peek [hex addr]\r\n");
    printf("led [on/off]\r\n");
    return 0;
}

static int cmd_peek(int argc, char *argv[]) {

    uint32_t addr = strtoul(argv[1], NULL, 16);
    uint32_t *reg = (uint32_t *) addr;

    if (addr % 4 != 0) {
        printf("error: peek address must be 4-byte aligned\n");
        return 1;
    }
    uint32_t n = 64;
    printf("Memory view @ %p\n", reg);
    print_memview(reg, n);

    return 0;
}

static int cmd_led(int argc, char *argv[]) {

    char *state = argv[1];
    if(strcmp(state,"on") == 0) {
        led_on(LED0_RED);
        return 0;
    }

    if(strcmp(state,"off") == 0) {
        led_off(LED0_RED);
        return 0;
    }

    return 0;
}