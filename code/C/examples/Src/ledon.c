#include "stdbool.h"
#include "inttypes.h"

void initialize(){
    /* initialize clock for GPIO C */
    * (uint32_t *) 0x4002104C |= 0x4;
    /* initialize led direction in mode register*/
    * (uint32_t *) 0x48000800 &= ~(1 << 13);
}

int main(void){
    bool state = false;
    initialize();
    * (uint32_t *) 0x48000814 &= ~(1 << 6);
}
