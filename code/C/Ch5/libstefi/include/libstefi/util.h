#include <stdint.h>

#define BIT(num) (1 << num)
#define GET_BITS(value, pos, num_bits) ( (value >> pos) & ((1U << num_bits) - 1) )

void soft_delay_ms(uint32_t time_in_ms);

#define TEXTIFY(x) #x
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1: __FILE__ )
#define ASSERT(expr) \
    do { \
        if(!(expr)) { \
        printf("Failed:%s, %d: %s\r\n", __FILENAME__, __LINE__, TEXTIFY(expr)); return; \
        } \
       } \
    while(0);
