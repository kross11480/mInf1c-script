# toggle led and stop app on alternate button press
import machine
import time

button = machine.Pin('B0', machine.Pin.IN, machine.Pin.PULL_UP)
led = machine.Pin('C7' ,machine.Pin.OUT)
state = 1
while True:
    if button.value() == 0:
        led.value(1) #switch off led
    else:
        led.value(not led.value())
        time.sleep(0.5)