add_library(DCMotorL298N STATIC l298n.c)

target_include_directories(DCMotorL298N PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(DCMotorL298N PUBLIC libstefi)