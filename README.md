# MIPS-interpreter

A simple **MIPS32 instruction set interpreter** written in C/C++ to explore instruction decoding and execution.

## Features
- Fetch–decode–execute loop
- 32 general-purpose registers and program counter
- Byte-addressable memory model
- Arithmetic, memory, and control-flow instructions
- Basic syscall support

## Supported Instructions
- Arithmetic/Logic: `add`, `addi`, `sub`, `and`, `or`, `slt`
- Memory: `lw`, `sw`
- Control Flow: `beq`, `bne`, `j`, `jal`, `jr`
- System: `syscall`

## Build & Run
```bash
g++ *.cpp
./a.out
