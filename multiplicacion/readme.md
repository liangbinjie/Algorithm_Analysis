# Ancient Multiplication Efficiency

This program compares the efficiency of different multiplication methods, including the ancient Russian Peasant method, across C and Assembly implementations.

## Description

The program generates 8 random numbers (0-999) to create a 4x4 table, resulting in 16 unique multiplications. It then calculates the execution time for these multiplications using three different methods in both C and Assembly:

1. Null Method: Returns 0 (control)
2. Standard Method: Regular multiplication (a * b)
3. Russian Peasant Method: An ancient multiplication algorithm

The program performs each multiplication N times to ensure accurate timing and also inverts the operands (B x A instead of A x B) for comprehensive analysis.

## Features

- Random number generation (0-999)
- 4x4 multiplication table creation
- Implementation in both C and Assembly
- Three multiplication methods:
  - Null Method
  - Standard Method
  - Russian Peasant Method
- Operand inversion
- Execution time measurement

## Installation

1. Clone the repository or download the source files.

2. Navigate to the project directory:

```bash
   $ cd directory/where/the/files/are
```

3. Compile the program using the provided Makefile:

```bash
$ make
```
This command will generate the executable file.

4. Run the program
```bash
$ ./main
```

Note: Ensure you have a C compiler (such as gcc) and an assembler (such as NASM) installed on your system. The Makefile assumes these are available in your system path.

## Dependencies

To compile and run this program, you'll need the following:

1. C Compiler (e.g., GCC)
   - Used to compile the C portions of the code

2. Assembler (e.g., NASM - Netwide Assembler)
   - Used to assemble the Assembly portions of the code

3. Make
   - Used to automate the compilation process

4. Standard C Library
   - For basic C functions used in the program

5. Operating System
   - Linux, Windows with WSL

