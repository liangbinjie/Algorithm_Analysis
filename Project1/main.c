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
    char originalInput[size+1];                                     // character array to store the input
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
    int row = 0;
    FILE *file;
    // Open a file in writing mode and write the latex content
    file = fopen("AA_PR01.tex", "w");
    fprintf(file, "%s", latexContent);
    fclose(file);

    // Open the file in append mode and write the table
    file = fopen("AA_PR01.tex", "a");
    // here goes execution table
    strncpy(originalInput, textInput, size);
    bubbleSort(file, textInput); //DONE
    strncpy(textInput, originalInput, size);
    insertionSort(file, textInput); //DONE
    strncpy(textInput, originalInput, size);
    exchangeSort(file, textInput); //DONE
    //mergeSort(file, textInput, 0, 15, &row);
    row = 0;
    //quickSort(file, textInput, 0 , 15, &row);
    row = 0;
    strncpy(textInput, originalInput, size);
    shellSort(file, textInput, size); //DONE
    strncpy(textInput, originalInput, size);
    gnomeSort(file, textInput); //DONE
    strncpy(textInput, originalInput, size);
    cocktailSort(file, textInput); 
    //stoogeSort(file, textInput, 0, size - 1, &row);

    fprintf(file, "\\end{document}");
    fclose(file);

    system("pdflatex AA_PR01.tex");                     // compile the latex file using pdflatex

    // system("evince --presentation AA_PR01.pdf");
  
    return 0;
}