ARMGNU ?= arm-none-eabi

AOPS = -g

all : firmware.bin

clean:
	rm -f *.o
	rm -f *.elf
	rm -f *.bin

blink_button.o : blink_button.s
	$(ARMGNU)-as $(AOPS) blink_button.s -o blink_button.o

firmware.bin: blink_button.o
	$(ARMGNU)-ld -Ttext=0x8000000 blink_button.o -o blink_button.elf
	$(ARMGNU)-objcopy -O binary blink_button.elf firmware.bin