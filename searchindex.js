Search.setIndex({"docnames": ["Kapitel/01/Kit", "Kapitel/01/Tools", "Kapitel/01/WhyEmbedded", "Kapitel/02/state_machine", "Kapitel/03/Timer", "Kapitel/03/baremetal", "Kapitel/03/gpio", "Kapitel/Exercise/01_LED", "Kapitel/Exercise/02_ReactionTimer", "Kapitel/Exercise/Praktika", "intro", "notebooks", "test_upython"], "filenames": ["Kapitel/01/Kit.md", "Kapitel/01/Tools.md", "Kapitel/01/WhyEmbedded.md", "Kapitel/02/state_machine.md", "Kapitel/03/Timer.md", "Kapitel/03/baremetal.md", "Kapitel/03/gpio.md", "Kapitel/Exercise/01_LED.ipynb", "Kapitel/Exercise/02_ReactionTimer.ipynb", "Kapitel/Exercise/Praktika.md", "intro.md", "notebooks.ipynb", "test_upython.ipynb"], "titles": ["Kit", "<span class=\"section-number\">1. </span>What are Embedded Systems?", "<span class=\"section-number\">1.1. </span>Why study Embedded Systems?", "<span class=\"section-number\">2. </span>Events and State", "<span class=\"section-number\">4. </span>Timer", "<span class=\"section-number\">3.3. </span>BareMetal I/O", "<span class=\"section-number\">3. </span>General Purpose Input and Output", "<span class=\"section-number\">5.1. </span>Exercise 1: LED Chaser", "&lt;no title&gt;", "<span class=\"section-number\">5. </span>Praktika", "Embedded Systems", "Content with notebooks", "<span class=\"section-number\">1.3. </span>Getting Started"], "terms": {"thi": [0, 1, 3, 5, 6, 7, 9, 10, 11, 12], "cours": [0, 10], "logist": 0, "includ": [0, 11], "follow": [0, 1, 5, 6, 7, 12], "avail": [0, 5], "embed": [0, 3, 5, 6], "system": [0, 3, 5, 6], "lab": [0, 10], "stm32": [0, 5, 12], "board": [0, 10, 12], "stefi": [0, 7], "shield": [0, 7], "usb": 0, "cabl": 0, "comput": [0, 1, 2], "github": 0, "account": 0, "skip": 1, "section": [1, 5], "If": [1, 6], "you": [1, 2, 3, 5, 6, 10, 11], "have": [1, 3, 5, 6], "heard": 1, "microcontrol": [1, 5, 6, 7, 8, 10, 12], "know": 1, "refer": [1, 5], "all": [1, 3, 5, 6], "devic": [1, 5, 7, 10, 12], "gadget": 1, "from": [1, 4, 5, 6, 7, 8, 10, 11], "coffe": [1, 6], "machin": [1, 2, 5, 6, 7, 8, 10, 12], "car": 1, "which": [1, 5, 6, 7], "enabl": [1, 2, 5, 10], "small": 1, "few": 1, "sensor": [1, 5, 10], "actuat": [1, 10], "power": [1, 5, 6], "suppli": 1, "unit": 1, "chicken": 1, "feed": 1, "Such": 1, "gener": [1, 4, 5, 10], "purpos": [1, 5, 10], "design": 1, "domain": 1, "specif": [1, 5], "These": [1, 5], "ubiquit": 1, "one": [1, 3, 5, 6, 7], "more": [1, 11], "characterist": 1, "i": [1, 7, 10, 11, 12], "need": [1, 5, 6], "detect": 1, "other": [1, 6, 7], "vehicl": 1, "my": 1, "blind": 1, "spot": 1, "camera": [1, 5], "warn": 1, "fast": 1, "enough": [1, 2], "real": [1, 7, 10], "time": [1, 3, 4, 7, 8], "high": [1, 5, 6], "perform": [1, 3, 5], "mai": 1, "hurt": 1, "somebodi": 1, "ha": [1, 3, 5, 6, 12], "unintend": 1, "behavior": 1, "safeti": 1, "critic": 1, "do": [1, 5, 7, 10, 11], "want": [1, 11], "chang": [1, 6, 7], "batteri": 1, "forev": [1, 3], "low": [1, 5, 6, 10], "let": 1, "me": 1, "connect": [1, 5, 6, 7, 12], "internet": 1, "wireless": 1, "your": [1, 2, 6, 11], "boss": 1, "just": [1, 2], "cheap": 1, "processor": [1, 10], "matur": 1, "toolchain": 1, "cost": 1, "market": 1, "There": [1, 7, 11], "mani": 1, "term": [1, 3], "like": [1, 5, 7], "physic": [1, 6], "thing": 1, "iot": 1, "cyber": 1, "also": [1, 5, 6, 11], "The": [1, 2, 3, 5, 6, 7, 10, 12], "brain": 1, "often": [1, 5, 6, 7], "call": [1, 8], "modern": [1, 5], "pack": 1, "multipl": [1, 5], "core": 1, "memori": [1, 10], "peripher": [1, 5, 10], "modul": [1, 8], "singl": 1, "packag": [1, 10], "respons": [1, 8], "housekeep": 1, "oper": [1, 5], "manag": 1, "non": 1, "volatil": [1, 5], "flash": [1, 5, 10, 12], "store": [1, 5], "firmwar": [1, 6], "code": [1, 3, 5, 6, 7, 10], "data": [1, 3, 5, 11], "even": 1, "when": [1, 5, 6], "switch": [1, 5, 6, 7, 12], "off": [1, 3, 5, 6], "ram": [1, 5, 10], "provid": [1, 5], "faster": 1, "access": [1, 5], "program": [1, 2, 3, 5, 6, 7, 10], "o": [1, 6], "gpio": [1, 5, 7, 10], "dac": 1, "adc": 1, "us": [1, 3, 5, 6, 7, 10, 12], "simpl": [1, 6, 10], "digit": [1, 6], "analog": [1, 6], "input": [1, 3, 4, 5, 10], "output": [1, 3, 4, 5, 10], "button": [1, 3, 5, 6, 7, 8], "led": [1, 3, 5, 12], "etc": [1, 11], "One": [1, 5], "should": [1, 5, 6, 7, 10], "forget": 1, "mighti": [1, 10], "timer": [1, 5, 8, 10], "none": 1, "could": 1, "been": 1, "realiz": [1, 7], "without": [1, 7], "interrupt": [1, 4, 7, 10], "veri": [1, 6], "certain": [1, 5, 6], "robust": [1, 10], "speed": [1, 5], "commun": [1, 3, 10], "therefor": [1, 3, 5, 6], "complex": 1, "spi": [1, 10], "i2c": [1, 10], "can": [1, 3, 5, 10, 11, 12], "contain": [1, 5, 9, 10], "compon": [1, 6], "clock": [1, 4, 5], "watchdog": 1, "thei": [1, 5, 6], "optim": [1, 7], "applic": [1, 5, 7], "about": [1, 6, 11], "acceler": 1, "dma": 1, "differ": [1, 6, 7], "between": [1, 6, 7], "microprocessor": 1, "8": [1, 10], "bit": [1, 4, 5, 6], "develop": [2, 6, 7, 10], "own": 2, "solv": [2, 10], "some": [2, 3, 5, 6, 11], "world": [2, 7, 10], "challeng": [2, 3], "problem": [2, 3, 6, 7, 10], "It": [2, 5], "fun": 2, "tangibl": 2, "learn": [2, 5], "deploi": [2, 3], "electron": 2, "humbl": 2, "state": [2, 6, 7, 8, 10, 11], "understand": [2, 7], "languag": [2, 5], "c": [2, 10], "rust": 2, "microzig": 2, "micropython": [2, 5, 7, 10, 12], "apollo": 2, "guidanc": 2, "agc": 2, "pioneer": 2, "work": [2, 3, 6, 11], "1960": 2, "onc": [3, 6], "ar": [3, 5, 6, 7, 10], "suppos": 3, "did": 3, "try": 3, "turn": [3, 5], "an": [3, 5, 6, 7], "option": 3, "form": 3, "infinit": 3, "loop": [3, 5, 7], "function": [3, 5, 6, 7, 11], "entail": 3, "check": [3, 7, 11], "user": [3, 6], "process": 3, "final": 3, "produc": 3, "simplest": [3, 12], "exampl": [3, 11], "would": [3, 5, 7], "toggl": [3, 7, 12], "base": [3, 5], "press": [3, 5, 6, 7, 8], "": [3, 11], "while": [3, 5, 7, 8], "true": [3, 6, 7, 8], "checkinput": 3, "processdata": 3, "produceoutput": 3, "superloop": 3, "run": [3, 7, 10, 12], "fundament": 3, "driven": 3, "hardwar": [3, 5], "elimin": 3, "unproduct": 3, "wait": 3, "poll": [3, 6, 10], "extern": [3, 4, 5, 6, 7], "defin": [3, 5, 7], "trigger": [3, 6, 7, 8], "handler": [3, 7, 8], "pin": [3, 5, 7, 8, 10, 12], "info": 3, "posit": 3, "argument": 3, "set": [3, 5, 6], "global": [3, 7, 8], "variabl": [3, 5, 7], "servic": 3, "routin": 3, "callback": [3, 7, 8, 10], "finit": 3, "number": 3, "e": [3, 5, 6], "g": [3, 5, 6], "chaser": [3, 5], "onli": [3, 5, 6], "determinist": 3, "spaghetti": [3, 10], "think": [3, 6], "instead": 3, "model": [3, 6, 7], "automat": 3, "easier": 3, "write": [3, 5, 6, 7], "debug": [3, 6], "test": [3, 6], "after": [3, 6, 7], "cur_stat": 3, "ev": 3, "nxt_state": 3, "pattern": [3, 7], "object": 3, "orient": 3, "larger": 3, "codebas": 3, "common": 3, "pitfal": [3, 7], "flag": 3, "unset": 3, "reaction": [3, 8], "1": [4, 5, 6, 8, 10, 11], "period": [4, 8], "task": [4, 5, 7], "schedul": [4, 7], "rto": 4, "2": [4, 5, 7, 8, 10], "accur": 4, "delai": [4, 5, 6, 7], "z": 4, "b": 4, "debounc": [4, 6, 7, 10], "stopuhr": 4, "bobsl": 4, "3": [4, 5, 7, 8, 10], "waveform": [4, 6], "motor": [4, 6], "control": [4, 5], "lcd": 4, "displai": 4, "4": [4, 5, 10, 11], "measur": 4, "durat": 4, "event": [4, 5, 6, 7, 8, 10], "tachomet": 4, "pwm": 4, "paramet": 4, "counter": 4, "mode": [4, 5, 6, 7, 8], "16": [4, 5], "32": [4, 5], "up": [4, 5, 7, 8, 12], "down": [4, 5], "prescal": 4, "precis": 4, "v": 4, "length": 4, "found": [6, 7, 11], "In": [5, 6, 7, 8], "interact": [5, 6, 11], "interfac": 6, "pushbutton": 6, "pressur": 6, "slide": 6, "door": 6, "word": 6, "suggest": 6, "valu": [5, 6, 7, 8], "0": [5, 6, 7, 8, 11], "signifi": 6, "fals": [6, 7, 8], "obtain": 6, "appli": [6, 10], "voltag": [5, 6], "read": [5, 6, 7, 10], "regist": 6, "For": [5, 6, 11], "light": [5, 6, 7, 10], "emit": 6, "diod": 6, "glow": 6, "amount": 6, "current": 6, "flow": [5, 6], "through": [5, 6], "v_cc": 6, "over": 6, "limit": 6, "resistor": [5, 6, 7], "On": [6, 10], "here": [5, 6, 7, 11], "softwar": [5, 6], "relev": [5, 6], "so": [6, 7], "correspond": 6, "mean": [5, 6, 11], "doe": [5, 6, 7], "altern": [5, 6], "lead": 6, "lighten": 6, "festiv": 6, "season": 6, "A": [5, 6, 10], "push": [5, 6, 7], "pb1": 6, "ground": 6, "howev": 6, "releas": 6, "float": 6, "nois": 6, "piezo": 6, "electr": 6, "lighter": 6, "caus": 6, "inadvert": 6, "address": [5, 6], "issu": [6, 10], "consist": 6, "part": 6, "implement": [5, 6], "logic": [5, 6, 7], "where": [5, 6, 7], "statu": [5, 6], "goe": 6, "whenev": 6, "live": 6, "determin": 6, "import": [6, 7, 8, 11, 12], "correct": [5, 6], "port": [5, 6], "signal": 6, "whether": 6, "fall": 6, "rise": 6, "flank": 6, "transit": 6, "respect": [5, 6, 7], "requir": 6, "possibl": 6, "solut": 6, "architectur": 6, "aid": [6, 10], "flowchart": 6, "diagram": 6, "particularli": 6, "corner": 6, "case": [5, 6], "execut": 6, "begin": [6, 11], "long": [6, 10], "incorrect": 6, "reason": 6, "rare": 6, "commod": 6, "partli": 6, "lot": [5, 6, 11], "frustrat": 6, "utmost": 6, "valid": [6, 8], "depend": 6, "activ": [6, 10], "sleep": [5, 6, 7], "bounc": 6, "four": 7, "blink": 7, "sequenc": 7, "left": 7, "right": 7, "back": 7, "again": 7, "frequenc": 7, "hz": 7, "creat": [7, 11], "lauflicht": 7, "effect": 7, "appear": 7, "move": 7, "forth": 7, "start": [5, 7, 10], "stop": [7, 10], "chase": 7, "round": 7, "complet": 7, "aim": [7, 10], "practic": 7, "skill": 7, "schemat": [5, 6, 7, 10], "how": 7, "react": 7, "handl": 7, "perfect": 7, "see": [5, 7, 11], "upydevic": [7, 12], "kernel": [7, 12], "jupyt": [7, 11, 12], "serialconnect": [7, 11, 12], "dev": [7, 12], "tty": [7, 12], "usbmodem11203": [7, 12], "115200": [7, 12], "usageerror": [7, 11], "line": [5, 7, 8, 11], "magic": [7, 11], "concept": [5, 7], "yellow": 7, "what": [5, 7, 10], "pull": [5, 7], "intern": [5, 7], "written": 7, "onto": 7, "order": [5, 7], "c4": [7, 8], "c5": 7, "c6": [7, 8], "c7": 7, "out": [7, 8, 11, 12], "rang": [7, 11], "len": 7, "25": 7, "31mno": [7, 12], "0m": [7, 12], "websocketconnect": [7, 12], "lsmagic": [7, 12], "list": [7, 12], "command": [7, 12], "get": 7, "repeat": 7, "yourself": 7, "dry": 7, "introduc": 7, "make": [5, 7, 11], "modular": 7, "proper": 7, "name": [5, 7, 8], "constant": 7, "led_pin": 7, "125": 7, "def": [7, 8], "blink_l": 7, "iter": 7, "revers": 7, "divid": [5, 7], "conquer": 7, "most": [5, 7, 8], "seen": 7, "first": 7, "wa": 7, "consider": 7, "now": 7, "wai": 7, "chase_l": 7, "switchoff_l": 7, "primit": 7, "button_pressed_debounc": 7, "button_press": 7, "02": 7, "els": [7, 10], "b0": [7, 8], "IN": [7, 8], "pull_up": [7, 8], "irq": [7, 8], "irq_fal": [7, 8], "state_": [7, 8], "updat": 7, "elif": 7, "action": 7, "random": [8, 11], "set_reaction_tim": 8, "ev_btn": 8, "handler_tim": 8, "ev_tim": 8, "idl": 8, "readi": 8, "invalid": 8, "player": 8, "late": 8, "initi": [5, 8], "green_l": 8, "red_l": 8, "s0_button": 8, "expir": 8, "tr": 8, "t1": 8, "print": 8, "init": 8, "int": 8, "5000": 8, "1000": 8, "one_shot": 8, "ticks_m": 8, "wake": 8, "happi": 8, "modulenotfounderror": 8, "traceback": 8, "recent": 8, "last": 8, "cell": 8, "No": 8, "chapter": [5, 9, 10], "script": 10, "lectur": 10, "minf1c": 10, "georg": 10, "simon": 10, "ohm": 10, "univers": 10, "scienc": 10, "main": [5, 10], "next": 10, "content": 10, "exercis": [5, 10, 12], "prerequisit": 10, "summari": 10, "basic": 10, "pullup": 10, "asynchron": 10, "5": [10, 11], "distanc": 10, "6": 10, "graphic": 10, "7": 10, "bare": 10, "metal": 10, "map": 10, "assembl": [5, 10], "9": 10, "race": 10, "condit": 10, "concurr": 10, "praktika": 10, "book": 11, "As": [5, 11], "emb": 11, "imag": 11, "html": 11, "post": 11, "add_": 11, "math": 11, "align": 11, "mbox": 11, "la_": 11, "tex": 11, "end": 11, "But": 11, "sure": 11, "escap": 11, "dollar": 11, "sign": 11, "keep": 11, "well": 11, "inform": [5, 6, 11], "guid": 11, "document": 11, "sampl": 11, "matplotlib": 11, "rcparam": 11, "cycler": 11, "pyplot": 11, "plt": 11, "numpi": 11, "np": 11, "ion": 11, "contextlib": 11, "exitstack": 11, "0x106ae86d0": 11, "fix": 11, "reproduc": 11, "seed": 11, "19680801": 11, "n": 11, "10": 11, "logspac": 11, "100": 11, "randn": 11, "ii": 11, "arrai": [5, 11], "t": 11, "cmap": 11, "cm": 11, "coolwarm": 11, "ax": 11, "prop_cycl": 11, "color": 11, "linspac": 11, "line2d": 11, "custom_lin": 11, "lw": 11, "fig": 11, "subplot": 11, "figsiz": 11, "plot": 11, "legend": 11, "cold": 11, "medium": 11, "hot": 11, "bring": 12, "ani": 12, "plai": 12, "fade": 12, "notebook": 12, "31mdevic": 12, "reachabl": 12, "devicenotfound": 12, "serialdevic": 12, "a5": 12, "initialis": [], "configur": 5, "meet": [], "admonit": [], "fear": [5, 6], "find": [5, 6], "needl": [5, 6], "datasheet": [5, 6], "stack": [5, 6], "alreadi": 5, "tutori": [], "rel": [], "familiar": [], "text": [], "editor": [], "unlik": 5, "level": 5, "better": 5, "direct": 5, "prefer": 5, "abstract": 5, "portabl": 5, "closer": 5, "we": 5, "pointer": 5, "mask": 5, "standard": 5, "librari": 5, "apart": 5, "cpu": 5, "programm": 5, "them": 5, "second": 5, "rcc": 5, "reset": 5, "ahb2enr": 5, "moder": 5, "idr": 5, "odr": 5, "pupdr": 5, "disabl": 5, "correctli": 5, "look": 5, "must": 5, "done": 5, "manual": 5, "describ": 5, "its": 5, "featur": 5, "instanc": 5, "each": 5, "our": 5, "allow": 5, "locat": 5, "repres": 5, "unsign": 5, "integ": 5, "uint32_t": 5, "4gb": 5, "space": 5, "region": 5, "0x40000000": 5, "ahb1": 5, "bu": 5, "0x40021000": 5, "similarli": 5, "gpioc": 5, "0x48000800": 5, "offset": 5, "0x14": 5, "calcul": 5, "0x48000814": 5, "load": 5, "byte": 5, "great": 5, "techniqu": 5, "const": 5, "gpioc_out": 5, "gpio_cout": 5, "0x4": 5, "abov": 5, "c2": 5, "thu": 5, "keyword": 5, "question": 5, "interview": 5, "give": 5, "quick": 5, "recap": 5, "012_baremet": [], "baremet": [], "storag": 5, "declar": 5, "type": 5, "instruct": 5, "arithmet": 5, "express": 5, "alu": 5, "branch": 5, "beginn": 5, "cryptic": 5, "arrow": 5, "tild": 5, "hold": 5, "datatyp": 5, "cortex": 5, "point": 5, "relat": 5, "group": 5, "togeth": 5, "struct": 5, "field": 5, "member": 5, "although": 5, "repetit": 5, "error": 5, "prone": 5, "structur": 5, "associ": 5, "same": 5, "otyp": 5, "ospeedr": 5, "bsrr": 5, "lckr": 5, "lock": 5, "afr": 5, "macro": 5, "easi": 5, "void": 5, "toggle_l": 5, "po": 5, "led_po": 5}, "objects": {}, "objtypes": {}, "objnames": {}, "titleterms": {"kit": 0, "hardwar": 0, "softwar": 0, "option": 0, "what": [1, 2, 3, 4], "ar": 1, "embed": [1, 2, 10], "system": [1, 2, 10], "why": [2, 3, 4], "studi": 2, "skill": 2, "would": 2, "i": [2, 3, 4, 5, 6], "gain": 2, "histori": 2, "event": 3, "state": 3, "interrupt": 3, "machin": 3, "do": [3, 4], "need": [3, 4], "timer": 4, "gener": 6, "purpos": 6, "input": 6, "output": [6, 11], "initialis": 6, "pin": 6, "configur": 6, "pull": 6, "up": 6, "down": 6, "forev": 6, "loop": 6, "applic": 6, "how": 6, "can": 6, "blink": 6, "my": 6, "led": [6, 7], "meet": 6, "real": 6, "world": 6, "exercis": 7, "1": 7, "chaser": 7, "praktika": 9, "content": 11, "notebook": 11, "markdown": 11, "myst": 11, "code": 11, "block": 11, "get": 12, "start": 12, "you": [], "should": [], "have": [], "fear": [], "read": [], "schemat": [], "find": [], "relev": [], "needl": [], "inform": [], "datasheet": [], "stack": [], "alreadi": [], "know": [], "In": [], "order": [], "complet": [], "thi": [], "tutori": [], "rel": [], "familiar": [], "us": [], "command": [], "line": [], "well": [], "text": [], "editor": [], "012_baremet": [], "o": 5, "let": 5, "u": 5, "go": 5, "bare": 5, "metal": 5, "regist": 5, "memori": 5, "map": 5, "c": 5, "baremet": 5}, "envversion": {"sphinx.domains.c": 3, "sphinx.domains.changeset": 1, "sphinx.domains.citation": 1, "sphinx.domains.cpp": 9, "sphinx.domains.index": 1, "sphinx.domains.javascript": 3, "sphinx.domains.math": 2, "sphinx.domains.python": 4, "sphinx.domains.rst": 2, "sphinx.domains.std": 2, "sphinx.ext.intersphinx": 1, "sphinxcontrib.bibtex": 9, "sphinx": 60}, "alltitles": {"Kit": [[0, "kit"]], "Hardware": [[0, "hardware"]], "Software": [[0, "software"]], "Optional": [[0, "optional"]], "What are Embedded Systems?": [[1, "what-are-embedded-systems"]], "Why study Embedded Systems?": [[2, "why-study-embedded-systems"]], "What skills would i gain?": [[2, "what-skills-would-i-gain"]], "History": [[2, "history"]], "Events and State": [[3, "events-and-state"]], "Interrupts": [[3, "interrupts"]], "State Machine": [[3, "state-machine"]], "What is a state and a state machine?": [[3, "what-is-a-state-and-a-state-machine"]], "Why do i need a state machine": [[3, "why-do-i-need-a-state-machine"]], "Timer": [[4, "timer"]], "Why do i need a timer?": [[4, "why-do-i-need-a-timer"]], "What is a timer?": [[4, "what-is-a-timer"], [4, "id1"]], "Exercise 1: LED Chaser": [[7, "exercise-1-led-chaser"]], "Praktika": [[9, "praktika"]], "Content with notebooks": [[11, "content-with-notebooks"]], "Markdown + notebooks": [[11, "markdown-notebooks"]], "MyST markdown": [[11, "myst-markdown"]], "Code blocks and outputs": [[11, "code-blocks-and-outputs"]], "Getting Started": [[12, "getting-started"]], "General Purpose Input and Output": [[6, "general-purpose-input-and-output"]], "Initialisation": [[6, "initialisation"]], "Pins and their Configuration": [[6, "pins-and-their-configuration"]], "Pull-ups and Pull-downs": [[6, "pull-ups-and-pull-downs"]], "Forever Loop for Application": [[6, "forever-loop-for-application"]], "How can i blink my LED?": [[6, "how-can-i-blink-my-led"]], "My application meets Real World": [[6, "my-application-meets-real-world"]], "Embedded Systems": [[10, "embedded-systems"]], "BareMetal I/O": [[5, "baremetal-i-o"]], "Let us go bare-metal!": [[5, "let-us-go-bare-metal"]], "Registers": [[5, "registers"]], "Memory Map": [[5, "memory-map"]], "C": [[5, "c"]]}, "indexentries": {}})