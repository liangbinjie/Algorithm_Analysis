# Getting ASCII Characters Frecuency from Files

This document outlines a program that computes the frequency of ASCII characters across multiple files. The utility is designed to process files, identify all ASCII characters present, and generate a report detailing how often each character appears.

## Features

- Read files from command line
- Process files from the command line
- Generate a frecuency report file to be printed

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
$ ./main <frec_filename> <file_1> <file_2> ... <file_n>
```

Note: Ensure you have GCC Compiler installed on your system. The Makefile assumes these are available in your system path.

## Dependencies

To compile and run this program, you'll need the following:

1. GCC - C Compiler
   - Used to compile the C portions of the code

2. Make
   - Used to automate the compilation process

3. Standard C Library
   - For basic C functions used in the program

4. Operating System
   - Ubuntu Linux, Windows with WSL
   