import machine
import time
from random import random


class State:
    def handleInput(self):
        pass


class IdleState(State):
    def __init__(self, game) -> None:
        self.game = game
        self.game.green_led.value(1)
        self.game.red_led.value(1)

    def handleInput(self):
        if self.game.ev_btn:
            self.game.green_led.value(0)
            self.game.state = ReadyState(self.game)
            self.game.ev_btn = False


class ReadyState(State):
    def __init__(self, game) -> None:
        self.game = game
        self.game.green_led.value(0)
        self.game.timer.init(period=int(random() * 4000 + 1000), mode=machine.Timer.ONE_SHOT,
                             callback=self.game.handler_timer)

    def handleInput(self):
        if self.game.ev_tim:
            self.game.green_led.value(1)
            self.game.state = PlayState(self.game)
            self.game.ev_tim = False
        if self.game.ev_btn:
            self.result = -1
            self.game.state = ResultState(self.game)


class PlayState(State):
    def __init__(self, game) -> None:
        self.game = game
        self.game.red_led.value(0)
        self.t1 = time.ticks_ms()

    def handleInput(self):
        if self.game.ev_btn:
            self.game.result = time.ticks_ms() - self.t1
            self.game.state = ResultState(self.game)
            self.game.ev_btn = False


class ResultState(State):
    def __init__(self, game) -> None:
        self.game = game

    def handleInput(self):
        if self.game.result == -1:
            print("Trigger Happy = -1")
        else:
            print("reaction time:", self.game.result)
        self.game.state = IdleState(self.game)


# context class
class ReactionGame:
    def __init__(self) -> None:
        self.green_led = machine.Pin('C6', machine.Pin.OUT)
        self.red_led = machine.Pin('C4', machine.Pin.OUT)
        self.s0_button = machine.Pin('B0', machine.Pin.IN, machine.Pin.PULL_UP)
        self.s0_button.irq(trigger=self.s0_button.IRQ_FALLING, handler=self.set_reaction_time)
        self.timer = machine.Timer()

        self.state = IdleState(self)
        self.ev_btn = False
        self.ev_tim = False
        self.result = -1

    def set_reaction_time(self, button):
        self.ev_btn = True

    def handler_timer(self, tim):
        self.ev_tim = True

    def run(self):
        while True:
            self.state.handleInput()


game = ReactionGame()
game.run()