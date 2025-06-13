add_library(SimpleIO STATIC
        board.c
        led.c
        button.c
        debounce.c
)

target_include_directories(SimpleIO PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SimpleIO PUBLIC libstefi)