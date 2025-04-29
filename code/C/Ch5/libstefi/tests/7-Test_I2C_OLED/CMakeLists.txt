set(TARGET_NAME test_i2cOLED) #filename change here

add_executable(${TARGET_NAME} ${TARGET_NAME}.c ssd1306.c)
target_link_libraries(${TARGET_NAME} PRIVATE libstefi)
# Add internal headers to include path with 'internal' subdirectory
target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src  # Parent directory of 'internal'
)
