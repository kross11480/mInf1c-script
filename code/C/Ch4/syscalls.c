#include <sys/stat.h>
#include<stdio.h>
#include <unistd.h>
#include "uart.h"

int _write(int file, const char *ptr, int len) {
    if (file == STDOUT_FILENO || file == STDERR_FILENO) {
        for (int i = 0; i < len; i++) {
            uart_poll_out(ptr[i]);
        }
        return len;
    }
    return -1;
}

void *_sbrk(int incr) {
    extern char _end;
    static unsigned char *heap = NULL;
    unsigned char *prev_heap;
    if (heap == NULL) heap = (unsigned char *) &_end;
    prev_heap = heap;
    heap += incr;
    return prev_heap;
}

void _fstat(int fd, struct stat *st) {}
void _close(int fd) {}
void _isatty(int fd) {}
void _lseek(int fd, int ptr, int dir) {}
void _read(int fd, char *ptr, int len) {}
void _kill(int pid, int sig) {}
void _getpid(void) {}

_Noreturn void _exit(int status) {
    (void) status;
    for (;;) __asm__ volatile("BKPT #0");
}
