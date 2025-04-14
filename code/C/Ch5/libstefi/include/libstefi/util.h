#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define BIT(num) (1 << num)
#define GET_BITS(value, pos, num_bits) ( (value >> pos) & ((1U << num_bits) - 1) )

void soft_delay_ms(uint32_t time_in_ms);


#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1: __FILE__ )
#define TEXTIFY(x) #x
#define assert(expr) \
    do { \
        if(!(expr)) { \
        printf("Failed :%s, %d: %s\r\n", __FILENAME__, __LINE__, TEXTIFY(expr)); \
        while(1); \
        } \
       } \
    while(0);
