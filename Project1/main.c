#include <string.h>
#include <stdlib.h>
#include "algorithms.h"

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
    file = fopen(FILENAME, "w");
    fprintf(file, "%s", latexContent);
    fclose(file);

    // Open the file in append mode and write the table
    file = fopen(FILENAME, "a");
    // here goes execution table
    bubbleSort(file, textInput);

    fprintf(file, "\\end{document}");
    fclose(file);

    system("pdflatex AA_PR01.tex");                     // compile the latex file using pdflatex
  
    return 0;
}

