#include "shell.h"
#include "shell_cmd.h"

#include <stdio.h>
#include <string.h>
#include <libstefi/uart.h>

typedef int (*command_fn_t)(int argc, char *argv[]);
typedef struct {
    const char *command_name;
    command_fn_t fn;
} command_t;

command_t commands[] = {
    {"help", cmd_help},
    {"peek", cmd_peek},
    {"led", cmd_led},
};

const int num_commands = sizeof(commands)/sizeof(commands[0]);

void shell_readline(char buf[], size_t bufsize) {
    size_t len = 0;
    while(len < bufsize) {
        char c = uart_getchar();
        if(c == '\r' || c == '\n') {
            break;
        }
        buf[len++] = c;
        uart_putchar(c);
    }
    buf[len] = '\0';
    printf("\n");
}

int shell_evaluate(const char *line) {
    char buf[MAX_LINE_LEN];
    char *argv[MAX_TOKENS];
    int argc = 0;
    strcpy(buf, line);

    char *token = strtok(buf, " \t\r\n");
    while(token != NULL && argc < MAX_TOKENS) {
        argv[argc++] = token;
        token = strtok(NULL, " \t\r\n"); //continue parsing same string
    }

    for(int i=0; i < num_commands; i++) {
        if(strcmp(argv[0], commands[i].command_name) == 0) {
            return commands[i].fn(argc, argv);
        }
    }
    printf("command not found: %s\r\n", argv[0]);
    return argc;
}

void shell_init() {
    printf(" \r\n");
    printf("    _____ _______ ______ ______ _____\r\n");
    printf("   / ____|__   __|  ____|  ____|_   _| \r\n");
    printf("  | (___    | |  | |__  | |__    | | \r\n");
    printf("   |___ |   | |  |  __| |  __|   | | \r\n");
    printf("   ____) |  | |  | |____| |     _| |_ \r\n");
    printf("  |_____/   |_|  |______|_|    |_____| \r\n");
    printf(" \r\n");
    printf("Test Shell (type help for Info) \r\n");
    setvbuf(stdout, NULL, _IONBF, 0);
}

void shell_run() {
    char line[MAX_LINE_LEN];
    printf(">");
    shell_readline(line, sizeof(line));
    shell_evaluate(line);
}
