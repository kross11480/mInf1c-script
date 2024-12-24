# set linker script
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/link.ld)

# compiler and linker options
add_compile_options(-mcpu=cortex-m4 -mthumb)
add_compile_options(-g -Wall -std=c99 -ffreestanding)
add_link_options(-Wl,--print-memory-usage)
add_link_options(-mcpu=cortex-m4 -mthumb)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/link.ld)
add_link_options(-T ${LINKER_SCRIPT} -nostdlib)