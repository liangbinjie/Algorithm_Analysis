#include <stdio.h>

int size = 16;                                                  // define global variable for the size of the input          

int checkString(char textInput[]) {                             // function to check if the input is valid
    for (int i = 0; i < size; i++) {
        if (textInput[i] < 'A' || textInput[i] > 'Z') {
            return 0;
        }
    }
    return 1;
}

void bubbleSort(char list[]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (list[j] > list[j+1]) {
                char temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
                printf("%s | %c %c\n", list, list[j], list[j+1]);
            }
        }
    }
}

int main() {
    char textInput[size+1];                                     // character array to store the input
    int validInput = 0;                                         // boolean to check if the input is valid

    while (validInput == 0) {                                   // while loop to keep asking for input until it is valid

        printf("Please enter 16 capital letters: \n");
        fgets(textInput, sizeof(textInput), stdin);
        if (checkString(textInput) == 1) {                      // check if the input is valid
            validInput = 1;
        } else {
            printf("Invalid input. ");
        }
    }

    bubbleSort(textInput);                                      // sort the input in ascending order
    printf("The sorted input is: %s\n", textInput);             // print the sorted input

  
    return 0;
}

