#include <stdio.h>
#include "algorithms.h"
#include "latex.h"

// function to create the table, with its title and reference
void createTable(FILE *file, char sortName[], char textInput[]) {
    // create section title
    // create table structure
    fprintf(file, "\\section{%s}\n%s\n", sortName, tableHeader);

    // label the input
    for (int i = 0; i < size; i++) {
        fprintf(file, "& \\B{%c} ", textInput[i]);
    }
    fprintf(file, "\\\\\n\\hline\n");
}

// function to close the table
void closeTable(FILE *file, char sortName[]) {
    fprintf(file, "\\end{tabularx}\n\\caption{Execution Trace of \\textbf{%s}}\n\\label{T:%s}\\end{table}\n", sortName, sortName);
    fclose(file);
}

// function to check if the input is valid
int checkString(char textInput[]) {                             
    for (int i = 0; i < size; i++) {
        if (textInput[i] < 'A' || textInput[i] > 'Z') {
            return 0;
        }
    }
    return 1;
}

int main() {
    char textInput[size+1];                                     // character array to store the input
    int validInput = 0;                                         // boolean to check if the input is valid

    while (validInput == 0) {                                   // while loop to keep asking for input until it is valid

        printf("Please enter %d capital letters: \n", size);
        fgets(textInput, sizeof(textInput), stdin);
        if (checkString(textInput) == 1) {                      // check if the input is valid
            validInput = 1;
        } else {
            printf("Invalid input. ");                          // print error message
        }
    }

    FILE *file;
    // Open a file in writing mode and write the latex content
    file = fopen("AA_PR01.tex", "w");
    fprintf(file, "%s", latexContent);
    fclose(file);

    // Open the file in append mode and write the table
    file = fopen("AA_PR01.tex", "a");
    createTable(file, "Bubble Sort", textInput);
    // here goes execution table
    bubbleSort(file, textInput);
    closeTable(file, "Bubble Sort");

    file = fopen("AA_PR01.tex", "a");
    fprintf(file, "\\end{document}");
    fclose(file);
  
    return 0;
}

