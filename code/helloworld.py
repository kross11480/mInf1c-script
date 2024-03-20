import machine
import time

# Pin configurations
LED_PIN = 'C7'
BTN_PIN = 'B0'
DELAY_LEDTOGGLE = .5
DELAY_BTNREAD = .1

# Initialize pins
led = machine.Pin(LED_PIN, machine.Pin.OUT)
btn = machine.Pin(BTN_PIN, machine.Pin.IN, machine.Pin.PULL_UP)
#Initialize button state as 1 (not presses)
prev_btn = 1

def toggle_led(delay):
    """
    Toggle the LED state with a given delay.

    Args:
        delay (float): Time delay in seconds between LED toggles.
    """
    led.value(not led.value())
    time.sleep(delay)

def switch_off(delay):
    """Turn off the LED for a fixed duration."""
    led.value(1)
    time.sleep(delay)

def button_pressed():
    """
    Check if the button is pressed.

    Returns:
        bool: True if the button is pressed, False otherwise.
    """
    global prev_btn
    if btn.value() == 0 and prev_btn == 1:
        return True
    else:
        return False

def run_loop():
    """Main loop to run the program."""
    state = False
    global prev_btn
    while True:
        if button_pressed():
            state = not state
        prev_btn = btn.value()
        if state:
            toggle_led(DELAY_LEDTOGGLE)
        else:
            switch_off(DELAY_BTNREAD)

if __name__ == "__main__":
    run_loop()