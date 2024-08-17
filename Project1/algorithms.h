#include <stdio.h>
#include <stdbool.h>
#include "latex.h"

void bubbleSort(FILE* file, char list[]) {
    createTable(file, "Bubble Sort", list);
    int row = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (list[j] > list[j+1]) {
                char temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
            fprintf(file, "{\\bf %d} ", row++);
            for (int k=0; k < size; k++) {
                if (k==j || k==j+1) {
                    fprintf(file, "& \\X{%c} ", list[k]);
                } else {
                    fprintf(file, "& \\C{%c} ", list[k]);
                }
            }
            fprintf(file, "\\\\\n");
            if (row == 60) {
                closeTable(file, "Bubble Sort");
                createTable(file, "Bubble Sort 2", list);
            }
        }
    }
    closeTable(file, "Bubble Sort 2");
}

// format: 
// {\bf 01}& \X{D} & \X{L} & \C{Q} & \C{F} & \C{D} & \C{R} & \C{N} & \C{Q} & \C{S} & \C{D} & \C{W} & \C{A} & \C{L} & \C{O} & \C{K} & \C{D}\\
// {\\bf %d}
// & \\C{%c}
// & \\X{%c}

