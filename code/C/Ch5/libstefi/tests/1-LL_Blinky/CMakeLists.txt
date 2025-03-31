
add_executable(ll_blinky blinky.c)

target_link_libraries(ll_blinky PRIVATE libstefi)

# Add internal headers to include path with 'internal' subdirectory
target_include_directories(ll_blinky PRIVATE
        ${CMAKE_SOURCE_DIR}/src  # Parent directory of 'internal'
)

#target_include_directories(ll_blinky PRIVATE ../../src/internal)


