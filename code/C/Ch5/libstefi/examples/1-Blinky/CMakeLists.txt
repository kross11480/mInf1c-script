add_executable(blinky blinky.c ../../src/startup.c)

target_link_libraries(blinky libstefi)
