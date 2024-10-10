# Creating a Huffman Tree from a Frequency File

This program receives a frequency file and generates a Huffman tree in a h file. The frequency file can be generated from `Project2`.

## Features

Receive a frequency file from the command line
Process the frequency file and generate a Huffman tree .h file

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
$ ./main <frequency_file>
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
   
