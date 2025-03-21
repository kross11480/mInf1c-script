add_executable(blinky blinky.c startup.c)

target_link_libraries(blinky libstefi)
