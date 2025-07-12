# VIRTEL


## Description
Interpreter, using a bytecode virtual machine implemented in C, designed to execute compiled VIRTEL programs by translating source code into a compact, portable instruction set that the VM interprets at runtime.
- #### Interpreter's structure: [here](https://github.com/letv1nnn/VIRTEL/blob/main/info/interpreter_structure.md)
- #### the VIRTEL language: [here](https://github.com/letv1nnn/VIRTEL/blob/main/info/language_syntax.md)

## Clone and Run

   - **Clone**
   ```bash
   git clone https://github.com/letv1nnn/VIRTEL.git
   cd VIRTEL
   ```
   - **Branches** (info - Interpreter detailed info, src - source code and build system)
   ```bash
   cd info # enter the info dir
   ```
   ```bash
   cd src # enter the src dir
   ```
   - **Build, Run, Clean** - in src directory
   ```bash
   make # compiles the program
   ```
   ```bash
   ./virtel # runs the interpreter
   ```
   ```bash
   make clean # removes the ccompiled file
   ```
