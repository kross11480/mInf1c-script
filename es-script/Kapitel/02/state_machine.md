# Events and State

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

