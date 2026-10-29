# CHIP-8 Emulator

A CHIP-8 interpreter written in C++17, with rendering and input handled by raylib. It implements all 35 original opcodes, runs at about 660 instructions per second with 60 Hz timers, and plays games like Tetris.

![Tetris running in the emulator](docs/tetris.gif)

## Why I built it

I wanted a C++ project I could take from an empty repo to something visibly running, while working close to the hardware level: memory, registers, a stack, timers, and a framebuffer. CHIP-8 is small enough to finish and real enough to teach the fetch, decode, execute loop that every CPU runs.

## Features

* All 35 CHIP-8 opcodes, verified against the Timendus test suite ROMs in `roms/`
* Sprite drawing with XOR and collision detection on the 64 x 32 display, scaled 15x in a raylib window
* 16 key hexadecimal keypad mapped to the left side of a QWERTY keyboard
* Delay and sound timers that count down at 60 Hz
* A disassembler that prints any range of a ROM as readable instructions, used for debugging

## Building

Requires CMake 3.16 or newer and a C++17 compiler. raylib 5.5 is downloaded and built automatically by CMake, so there is nothing else to install. Tested on Linux (Ubuntu 20.04 with GCC 9.4).

```
git clone https://github.com/Sarellano1207/CHIP8.git
cd CHIP8
cmake -S . -B build
cmake --build build
```

## Running

Pass the path to a ROM:

```
./build/chip8 roms/IBM_Logo.ch8
./build/chip8 "roms/Tetris [Fran Dachille, 1991].ch8"
```

## Controls

| CHIP-8 keypad | Keyboard |
| --- | --- |
| 1 2 3 C | 1 2 3 4 |
| 4 5 6 D | Q W E R |
| 7 8 9 E | A S D F |
| A 0 B F | Z X C V |

## Design notes

* `Chip8` owns the whole machine state (4 KB of memory, 16 registers, the index register, program counter, stack, timers, and keypad) and exposes `cycle()`, `set_key()`, and `update_timers()`. It knows nothing about raylib.
* `Display` owns the raylib window and draws the framebuffer each frame. Keeping it separate means the emulator core could be driven by a different front end.
* The main loop runs 11 instructions per frame at 60 FPS, then ticks the timers once, which keeps timer speed correct no matter how fast the CPU is set.
* Where CHIP-8 interpreters historically disagree, this one uses the modern behavior: the shift instructions operate on VX, and FX55/FX65 leave the index register unchanged.

## Test ROMs

| ROM | What it checks |
| --- | --- |
| `1-chip8-logo.ch8` | Basic drawing |
| `3-corax+.ch8` | Opcode correctness |
| `4-flags.ch8` | The VF flag on math operations |
| `5-quirks.ch8` | Which historical behaviors are used |
| `6-keypad.ch8` | Keypad input |

Test ROMs are from Timendus's CHIP-8 test suite. Tetris is by Fran Dachille (1991).

## What I would add next

* Bounds checking on memory access through the index register and program counter
* Sound output when the sound timer is active
* Runtime flags to switch between the historical quirk behaviors
