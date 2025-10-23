# CH8: A Chip-8 Emulator

This is a simple Chip-8 emulator written in C++. It can be run in two different modes: with an SDL-based graphical interface, or with an ASCII-based interface in the terminal.

## Features

*   Chip-8 interpreter
*   SDL2 for graphics and input
*   ASCII mode for terminal-based rendering
*   Configurable clock speed
*   ROM loading

## Building

To build the emulator, you can use the provided `makefile`.

### SDL Version

To build the SDL version, which provides a graphical window for the emulator, run:

```bash
make sdl
```

This will create an executable named `out` in the `build` directory.

### ASCII Version

To build the ASCII version, which runs in the terminal, run:

```bash
make ascii
```

This will also create an executable named `out` in the `build` directory.

## Usage

To run the emulator, you need to provide a Chip-8 ROM file as a command-line argument.

For the SDL version:

```bash
./build/out roms/Pong.ch8
```

For the ASCII version:

```bash
./build/out roms/Pong.ch8
```

You can replace `roms/Pong.ch8` with the path to any other Chip-8 ROM file.

## ROMs

A few public domain ROMs are included in the `roms` directory:

*   `Pong.ch8`
*   `SpaceINV.ch8`
*   `test_opcode.ch8`
*   `tetris.ch8`

## Keypad Layout

The Chip-8 has a 16-key hexadecimal keypad. The mapping for this emulator is as follows:

| Keyboard | Chip-8 |
| :---: | :---: |
| `1` | `1` |
| `2` | `2` |
| `3` | `3` |
| `4` | `C` |
| `q` | `4` |
| `w` | `5` |
| `e` | `6` |
| `r` | `D` |
| `a` | `7` |
| `s` | `8` |
| `d` | `9` |
| `f` | `E` |
| `z` | `A` |
| `x` | `0` |
| `c` | `B` |
| `v` | `F` |