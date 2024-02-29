
# What are Embedded Systems?

```{note}
Skip this section, If
* you have heard of embedded systems, microcontroller.
* you know 
```
Embedded systems refer to all devices and gadget from coffee machines to cars which are enabled by a small computer, few sensors, actuators, a power supply unit and chicken feed. Such systems are not general purpose, but are designed for a domain specific purpose. These systems are ubiquitous and have one or more following characteristics:
* I need to detect other vehicles in my cars blind-spot with a camera and warn fast enough(real-time and high performance)
* I may hurt somebody if my system has unintended behavior (safety critical) 
* I do not want change batteries forever (low power)
* let me connect my system to the internet (wireless)
* You or your boss just needs a cheap processor with a mature toolchain (low cost and fast time to market)

There are many other terms like physical computing, internet of things (IoT), cyber-physical systems which also refer to embedded systems.



The brains of such a small computer are often also called microcontrollers. Modern microcontrollers pack multiple processor cores, memory, and peripheral modules in a single package.
* The processor cores are responsible for computation and housekeeping operations like power management.
* Non-volatile memory like Flash stores the firmware code and data even when the power is switched off. Volatile memory like RAM provides faster access to program data.
* I/O peripherals 
  * like GPIO, DAC, ADC are used for connecting the microcontroller to simple digital and analog inputs and outputs like buttons, leds, etc. 
  * One should not forget the mighty timer. None of the real-time embedded system could have been realized without timer and interrupts.
  * Very often, certain sensors and actuators need robust high speed communication with the microcontroller. Therefore, microcontrollers have more complex peripherals like SPI, I2C, CAN, ADC, DAC etc.
  * The microcontroller also contain components like power and clock management unit, Real time clock, watchdog timer. They are needed to optimize embedded systems for low power and safety critical embedded applications.
  * What about accelerators and DMA

```{note}
* What is the difference between a microcontroller and microprocessor?
* What is a 8-bit microcontroller?
```

