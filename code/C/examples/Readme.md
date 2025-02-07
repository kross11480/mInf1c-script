

Use cmake to compile the examples in build directory


💡  cmake -S . -B build/

</aside>

Release the Book

<aside>
💡  ghp-import -n -p -f _build/html

</aside>
Use openocd to flash onto the hardware device 
openocd -f st_nucleo_l4.cfg -c "program build/led.elf verify reset"