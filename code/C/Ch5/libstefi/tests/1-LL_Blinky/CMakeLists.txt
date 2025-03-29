add_executable(ll_blinky blinky.c ../../src/startup.c)

target_link_libraries(ll_blinky libstefi)
