
add_executable(test_gpio test_gpio.c)

target_link_libraries(test_gpio PRIVATE libstefi)

# Add internal headers to include path with 'internal' subdirectory
target_include_directories(test_gpio PRIVATE
        ${CMAKE_SOURCE_DIR}/src  # Parent directory of 'internal'
)

#target_include_directories(ll_blinky PRIVATE ../../src/internal)
