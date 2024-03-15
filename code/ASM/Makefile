ARMGNU ?= arm-none-eabi

AOPS = -g

program = toggle_led_bug
srcs := $(wildcard *.s)
objects := $(srcs:.s=.o)

all : $(program).bin

clean:
	rm -f *.o
	rm -f *.elf
	rm -f *.bin

%.o : %.s
	$(ARMGNU)-as $(AOPS) -o $@ $<
%.elf : %.o
	$(ARMGNU)-ld -Ttext=0x8000000 $< -o $@
%.bin : %.elf
	$(ARMGNU)-objcopy -O binary $< $@
