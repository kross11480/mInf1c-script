# Events and State

The embedded systems once deployed are supposed to work forever. "Did you try turning it off and on?" is not an option. Therefore, all embedded system have some form of infinite loop that performs all the functions of the system. This entails checking for user or system inputs, doing some data processing, and finally producing some output. The simplest example would be to toggle an led based on a button press and s
```python
while True:
    checkInput()
    processData()
    produceOutput()
```
S
* Superloop is a infinite loop running forever, a fundamental in event-driven programming

## Interrupts
Hardware interrupts eliminating unproductive waiting time in polling loops, waiting for external events.
* define trigger (), and handler
* handler, pin info is positional argument, set global variable for communication
* 
## State Machine
* What are Interrupts (trigger, events, polling)?
* What is interrupt service routine (Callback, Handler)? 
* What is a state and a state machine?
* Why do i need a state machine?
* 

## What is a state and a state machine?

State machine has
* finite number of states (e.g. led chaser is "on", "off")
* can only be in one state at a time (deterministic)
* events are inputs to the state machine (e.g. button press)

## Why do i need a state machine
* Spaghetti Code (Problem: think in terms of event instead of state)
* modeling the problem (Challenge: What are the states of the automat)
* Easier writing, debugging, and testing code after modelling (if cur_state=on: if ev: nxt_state = ..)
* State pattern in object oriented programming used in larger codebase

#Common Pitfalls
* event flag not unset after reaction

