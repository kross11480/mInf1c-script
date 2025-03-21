

'''
libstefi/
├── include/          # Public API headers
│   ├── libstefi/        # Library namespace
│   │   ├── mylib.h   # Umbrella header
│   │   ├── gpio.h    # GPIO API
│   │   ├── uart.h    # UART API
│   │   ├── timer.h   # Timer API
│   │   └── config.h  # Configuration options
├── src/              # Implementation files
│   ├── gpio.c
│   ├── uart.c
│   ├── timer.c
│   ├── internal/     # Private headers (for register map and macros)
│   │   ├── gpio_internal.h
│   │   ├── uart_internal.h
│   │   └── timer_internal.h
├── examples/         # Usage examples
│   ├── blink_led/
│   ├── uart_printf/
│   ├── timer_pwm/
├── tests/            # Unit tests (if applicable)
├── cmake/            # CMake module (if needed)
├── CMakeLists.txt    # CMake build script
└── README.md         # Documentation
'''
