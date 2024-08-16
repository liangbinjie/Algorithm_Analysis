#include <stdio.h>

int size = 16;
char latexOutput[] = "";

void bubbleSort(FILE* file, char list[]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (list[j] > list[j+1]) {
                char temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
            
        }
    }
}

// format: 
// {\bf 01}& \X{D} & \X{L} & \C{Q} & \C{F} & \C{D} & \C{R} & \C{N} & \C{Q} & \C{S} & \C{D} & \C{W} & \C{A} & \C{L} & \C{O} & \C{K} & \C{D}\\
// {\\bf %d}
// & \\C{%c}
// & \\X{%c}