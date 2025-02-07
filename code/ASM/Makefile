ARMGNU ?= arm-none-eabi

AOPS = -g

program = toggle_led
srcs := $(wildcard *.s)
objects := $(srcs:.s=.o)

all : $(program).elf

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

openocd:
	@openocd $(OPENOCD_FLAGS)

debug:
	arm-none-eabi-gdb -ex "target extended-remote :3333" $(program).elf