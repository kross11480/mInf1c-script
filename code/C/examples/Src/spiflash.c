#include "inttypes.h"

/*RCC: Enable GPIOA Port A on AHB2 and SPI on APB2*/
volatile uint32_t *const rcc_ahb2clock_enable = (uint32_t *) 0x4002104C;
volatile uint32_t *const rcc_apb2clock_enable = (uint32_t *) 0x4002104C;

/*GPIO: Flash SPI(A4: CS, A5: SCK, A6: MISO, A7: MOSI) */
volatile uint32_t *const gpioa_moder = (uint32_t *) 0x48000000 + 0x00;
volatile uint32_t *const gpioa_afrl = (uint32_t *) 0x48000000 + 0x20;
volatile uint32_t *const gpioa_odr = (uint32_t *) 0x48000000 + 0x14;
volatile uint32_t *const gpioa_ospeed = (uint32_t *) 0x48000000 + 0x08;

/*SPI Registers */
volatile uint32_t *const spi1_sr = (uint32_t *) 0x40013000 + 0x08;;
volatile uint32_t *const spi1_dr = (uint32_t *) 0x40013000 + 0x0C;;
volatile uint32_t *const spi1_cr1 = (uint32_t *) 0x40013000 + 0x00;;
volatile uint32_t *const spi1_cr2 = (uint32_t *) 0x40013000 + 0x04;;

void set_bit(volatile uint32_t *const reg, int pos){
    *reg |= (1U << pos);
}

void clear_bit(volatile uint32_t *const reg, int pos){
    *reg &= ~(1U << pos);
}

void toggle_bit(volatile uint32_t *const reg, int pos){
    *reg ^= (1U << pos);
}

void set_bit_pattern(volatile uint32_t *const reg, uint32_t pattern)
{
    *reg |= pattern;
}

void clear_bit_pattern(volatile uint32_t *const reg, uint32_t pattern)
{
    *reg &= ~pattern;
}

void initialize(){
    /* initialize clock */
    set_bit(rcc_ahb2clock_enable, 0); // GPIOA: bit 0
    set_bit(rcc_apb2clock_enable, 12); // SPI: bit 12

    /* set gpio pins for spi alternate function */
    /* intialize PA5 for SPI(AF5) CLK */
    clear_bit_pattern(gpioa_afrl, 0xF<<20);
    set_bit_pattern(gpioa_afrl, 0x5<<20);
    /* intialize PA6 for SPI(AF5) MIS0 */
    clear_bit_pattern(gpioa_afrl, 0xF<<24);
    set_bit_pattern(gpioa_afrl, 0x5<<24);
    /* intialize PA7 for SPI(AF5) M0SI */
    clear_bit_pattern(gpioa_afrl, 0xF<<28);
    set_bit_pattern(gpioa_afrl, 0x5<<28);
    /*set mode of pin A4 to out and A5, A6, A7 to alternate function*/
    clear_bit_pattern(gpioa_moder, 0xFF<<8);
    set_bit_pattern(gpioa_moder, 0xA9<<8);

    /* initialize SPI1 parameters*/
    set_bit(spi1_cr1,2); //spi master
    set_bit(spi1_cr1,9); //software

    /* set low active CS as inactive */
    set_bit(gpioa_odr, 4);
}

void main()
{

}


