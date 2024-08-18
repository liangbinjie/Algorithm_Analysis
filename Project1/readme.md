# An Analysis of Different Sorting Algorithms

This program compares the efficiency of different sorting algorithms. It takes a string of 16 capital letters as input and generates a LaTeX PDF document with a detailed comparison of various sorting algorithms.

## Features

These are the sorting algorithms used:

- Insertion Sort
- Merge Sort
- Exchange Sort
- Quick Sort
- Bubble Sort
- Shell Sort
- Gnome Sort
- Cocktail Sort
- Stooge Sort

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
$ ./a.out
```

Note: Ensure you have GCC Compiler installed on your system. The Makefile assumes these are available in your system path.

## Dependencies

To compile and run this program, you'll need the following:

1. GCC - C Compiler
   - Used to compile the C portions of the code

2. Evince - PDF Viewer
   ```bash
   # Installation for Debian/Ubuntu Linux
   $ sudo apt-get update
   $ sudo apt-get install evince
   ```

3. LaTex Live - LaTex PDF generator
   ```bash
   # Installation for Debian/Ubuntu Linux
   $ sudo apt-get update
   $ sudo apt-get install texlive-latex-base
   $ sudo apt-get install texlive-publishers          # necessary for IEEE document compilation
   ```
   Note: For other operating systems, check out the following link: https://www.tug.org/texlive/
   
   LaTex-Live tgz file can be found on `Resources/install-tl-unx.tar.gz`

3. Make
   - Used to automate the compilation process

4. Standard C Library
   - For basic C functions used in the program

5. Operating System
   - Ubuntu Linux, Windows with WSL
   