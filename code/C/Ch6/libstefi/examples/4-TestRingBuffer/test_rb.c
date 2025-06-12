
#include <libstefi/uart.h>
#include "stdio.h"
#include "libstefi/ringbuffer.h"

#define CAPACITY 4
uint8_t buf[CAPACITY];
rb_t ringbuffer;
rb_t *rb;

void print_rb() {
    printf("ring buffer contents: ");
    while(!rb_is_empty(rb)) {
        printf("%d ", rb_remove(rb));
    }
    printf("\r\n");
}

int main(void) {
    uart_configure();
    printf("Test Ring Buffer \r\n");
    rb = &ringbuffer;

    rb_init(rb, buf, CAPACITY);

    // test insert
    rb_insert(rb, 12);
    rb_insert(rb, 13);
    print_rb();
    //test remove
    rb_insert(rb, 42);
    rb_insert(rb, 43);
    rb_remove(rb);
    print_rb();
    printf("The buffer is empty now: %s \r\n", rb_is_empty(rb) ? "True" : "False");
    rb_insert(rb, 12);
    rb_insert(rb, 13);
    rb_insert(rb, 14);
    printf("The buffer is full: %s \r\n", rb_is_full(rb) ? "True" : "False");
    rb_remove(rb);
    rb_insert(rb,15);
    print_rb();


    while(1) {
    }
}