# toggle led and stop app on alternate button press
import machine
import time

button = machine.Pin('B0', machine.Pin.IN, machine.Pin.PULL_UP)
led = machine.Pin('C7' ,machine.Pin.OUT)
FREQ = 1
DELAY = 1/(2* FREQ)
#toggle led when the button is pressed (level-triggered)
def version1():
    while True:
        if button.value() == 0: #toggle led
             led.value(not led.value())
             time.sleep(DELAY)
        else:
             led.value(1) #switch off led

#toggle led when the button is pushed once and switch off if pressed again (edge-triggered)
def version2():
     pass