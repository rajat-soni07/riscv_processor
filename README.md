# RISC-V Processor Simulator with 5-Stage Pipelining

## Overview
This project implements a 5-stage pipelined processor for the RISC-V instruction set architecture in C++. The processor supports basic arithmetic, logical, memory, and control flow instructions. It is designed to simulate the execution of RISC-V assembly programs and also shows the pipelining diagram for both forwarding type processor and non-forwarding type processor

## Features
- **5-Stage Pipeline**: Instruction Fetch, Instruction Decode, Execute, Memory Access, and Write Back.
- **Hazard Handling**: Implements data forwarding and stall mechanisms to handle data and control hazards.
- **Instruction Set**: Supports a subset of the RISC-V ISA, including arithmetic, logical, load/store, and branch instructions.
- **Pipelining diagrams**: Also returns pipelining diagrams for the given set of instructions.

## Requirements
- C++17 or later
- A C++ compiler (e.g., GCC, Clang)
- Make (optional, for building the project)

## Usage
1. Clone the repository:
 ```bash
    git clone https://github.com/rajat-soni07/riscv_processor.git
    cd riscv_processor
 ```
2. Build the project:
 ```bash
    cd src
    make
 ```
3. Run the processor with a RISC-V assembly file:
 ```bash
    cd src
    #For simulating the forwarding type processor -
    ./forward ../inputfiles/<file_name>.txt <cycle_count> 
    #For simulating the non-forwarding type processor -
    ./noforward ../inputfiles/<file_name>.txt <cycle_count> 
 ```

4. Run the processor for all the test cases present in `../inputfiles/`
 ```bash
    make test
    #This will generate pipeline diagrams for both processor types and all files present in ../inputfiles/
 ```
## Design Decisions 
### Repository Structure
- `src/`: Contains the source code for the processor.
    - `display.cpp`: Printing the pipeline diagram to `../outputfiles/` .
    - `processor.cpp`: Implements the pipelining logic for forwarding and non-forwarding type processors in the Processor class.
    - `registers.cpp`: Contains Register class that acts as a register file for the processor unit.
    - `memory.cpp`: Contains Memory class that acts as a memory unit for the processor unit. 
    - `instructions.cpp`: Decodes the machine code given.
    - `input.cpp`: For reading the instructions from the given `.txt` file
    - `Makefile`: Build script for the project.
        - `all`: Generate binaries for both forwarding and non-forwarding type processors.
        - `test`: Runs the compiled binaries for all the input files in `../inputfiles/`.
        - `clean`: Removes compiled files.
- `inputfiles/` - Contains test cases for the processor
    - `fib.txt` : Instructions for calculating Fibbonaci(5).
    - `loop.txt`: Instructions for demonstrating a simple loop.
    - `arrsum.txt`: Instructions for calculating the sum of an array.
    - `bubblesort.txt`: Instructions for performing bubble sort on an array.
    - `strcpy.txt`: Instructions for copying a string.
    - `strlen.txt`: Instructions for calculating the length of a string.
    - `strncpy.txt`: Instructions for copying a string upto a specified length.
- `outputfiles/` : Contains the pipeline diagrams (forwarding and non-forwarding) for all test cases in `inputfiles/`
- `README.md`: Documentation for the project.

### Processor Design
- The processor design **closely mirrors actual hardware behavior**. Computations, **register updates, and memory operations** are performed in their respective pipeline stages, ensuring an accurate simulation of a real-world pipelined processor.

- The processor is implemented as a class, encapsulating the entire pipeline. Each of the five pipeline stages is represented as a struct within the class to store intermediate data as the clock cycles progress. The class also includes functions to simulate the behaviour of a single clock cycle for both forwarding and non-forwarding type processors.

- **Branch and jump instructions are implemented** to function logically by accurately fetching register values, performing comparisons, and updating the program counter as needed.

### Register File and Memory Unit Design
- Register File
    - The `Register` class encapsulates the register file (implemented using an array of 32 integers), providing methods to read and write register values.
    - Special care is taken to handle the zero register (`x0`), which always holds the value `0` and cannot be modified.

- Memory Unit
    - The `Memory` class models the memory unit, supporting both read and write operations.
    - It is designed to handle byte-addressable memory, ensuring compatibility with the RISC-V ISA. It uses `hashmap` to store values at each byte.
    - Default values of all memory addresses is set to `0`.
### Instructions supported
- **R-Type Instructions**: `add`, `sub`, `mul`, `sll`, `xor`, `div`, `srl`, `sra`, `or`, `rem`, `and`
- **I-Type Instructions**: `addi`, `slli`, `slti`, `sltiu`, `xori`, `srli`, `srai`, `ori`, `andi`
- **Load from memory Instructions**: `lb`, `lh`, `lw`, `lhu`
- **Save to memory Instructions**: `sb`, `sh`, `sw`
- **Branch Instructions**: `beq`, `bne`, `blt`, `bge`, `bltu`, `bgeu`
- **Jump Instructions**: `jal`,`jalr`

*The code is written in a way that new instructions can be added quickly so there is a scope for adding more instructions*.

## Known Issues in our Implementation
- No support for double-word instructions.

## Sources Referred
- For example programs - https://marz.utk.edu/my-courses/cosc230/book/example-risc-v-assembly-programs/. (strlen.txt, strcpy.txt, strncpy.txt, arrsum.txt, bubblesort.txt)
- Hennessy and Patterson, Computer Organization - For processor diagrams and implementations.
- ChatGPT - For  machinecode values for differenet instruction *(opcodes, funct7, funct3, etc. values)*.

## Team Members
- Rajat Soni (2023CS10229)
- Krish Bhimani (2023CS10712)