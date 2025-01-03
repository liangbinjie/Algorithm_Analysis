#include <stdio.h>
#include <stdbool.h>
#include "latex.h"

// RQPONMLKJIHGFEDCBA

int checkMerge = 0;
int checkBubble = 0;
int checkQuick = 0;
int checkStooge = 0;

int insertionExpand = 0;

/**
 * Bubble Sort:
  
  A simple comparison-based sorting algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order. The process is repeated until the list is sorted. As larger elements "bubble" to the top (end of the list), the algorithm gets its name. Despite its simplicity, Bubble Sort is inefficient for large datasets.
 
 */
void bubbleSort(FILE *file, char list[])
{
    createTable(file, "Bubble Sort", list);
    int row = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (list[j] > list[j + 1])
            {
                char temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
            fprintf(file, "{\\bf %d} ", row++);
            for (int k = 0; k < size; k++)
            {
                if (k == j || k == j + 1)
                {
                    fprintf(file, "& \\X{%c} ", list[k]);
                }
                else
                {
                    fprintf(file, "& \\C{%c} ", list[k]);
                }
            }
            fprintf(file, "\\\\\n");
            if (row % 62 == 0)
            {
                checkBubble++;
                closeTable(file, "Bubble Sort");
                createTable(file, "Bubble Sort", list);
            }
        }
    }
    if (checkBubble < 1) {
        closeTable(file, "Bubble Sort");
    }
    else {
        closeTable(file, "Bubble Sort");
    }
}

/**
Insertion Sort:

Iteratively builds a sorted portion of the list by 
picking elements from the unsorted portion and inserting them into 
their correct position. It starts with the second element and compares 
it with the elements before it, shifting elements as necessary. This process 
is repeated for each subsequent element until the entire list is sorted.

Falta: el pdf se corta, solo eso
 */
void insertionSort(FILE* file, char list[]) {
    createTable(file, "Insertion Sort", list); 
    int row = 0;
    int kCounter = 0;

    for (int i = 1; i < size; i++) {
        char key = list[i];
        int j = i - 1;

        int insertionIndex = i; 

        while (j >= 0 && list[j] > key) {
            //Print lista con la comparación inicial
            if (row % 30 == 0 && row != 0) {
                closeTable(file, "Insertion Sort");
                createTable(file, "Insertion Sort", list);
            }
            fprintf(file, "{\\bf %d} ", row);
            for (int k = 0; k < size; k++) {
                if (k == j || k == i) {
                    fprintf(file, "& \\X{%c} ", list[k]);  
                } else {
                    fprintf(file, "& \\C{%c} ", list[k]);
                }
            }
            fprintf(file, "\\\\\n");

            list[j + 1] = list[j];
            insertionIndex = j;
            j--;

            //Print luego del swap
            fprintf(file, "{\\bf %d} ", row++);
            for (int k = 0; k < size; k++) {
                if (k == j || k == i) {
                    fprintf(file, "& \\X{%c} ", list[k]);  
                } else {
                    fprintf(file, "& \\C{%c} ", list[k]);
                }
            }
            fprintf(file, "\\\\\n");
        }
        
        list[insertionIndex] = key;

        //Print final de elemento i
        fprintf(file, "{\\bf %d} ", row);
        for (int k = 0; k < size; k++) {
            if (k == insertionIndex || k == i) { //imprime el 
                fprintf(file, "& \\X{%c} ", list[k]);  
            } else {
                fprintf(file, "& \\C{%c} ", list[k]); 
            }
        }
        fprintf(file, "\\\\\n");
    }

    closeTable(file, "Insertion Sort");
}


/**
Exchange Sort:

Repeatedly compares and swaps adjacent elements if they are 
out of order. This process is repeated until the entire list is sorted. The 
algorithm continues to iterate through the list, exchanging elements as needed to 
ensure that each element is in its correct position.

Flata: se corta el pdf
 */
void exchangeSort(FILE* file, char list[]) {
    createTable(file, "Exchange Sort", list); 
    int row = 0; 

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (list[i] > list[j]) {


                char temp = list[i];
                list[i] = list[j];
                list[j] = temp;

                fprintf(file, "{\\bf %d} ", row++);
                if (row % 50 == 0 && row != 0)
                {
                    closeTable(file, "Exchange Sort");
                    createTable(file, "Exchange Sort", list);
                }
                for (int k = 0; k < size; k++)
                {
                    if (k == j || k == i)
                    {
                        fprintf(file, "& \\X{%c} ", list[k]);
                    }
                    else
                    {
                        fprintf(file, "& \\C{%c} ", list[k]);
                    }
                }
                fprintf(file, "\\\\\n");
            }

            fprintf(file, "{\\bf %d} ", row++);
            if (row % 50 == 0 && row != 0)
            {
                closeTable(file, "Exchange Sort");
                createTable(file, "Exchange Sort", list);
            }
            for (int k = 0; k < size; k++)
            {
                if (k == j || k == i)
                {
                    fprintf(file, "& \\X{%c} ", list[k]);
                }
                else
                {
                    fprintf(file, "& \\C{%c} ", list[k]);
                }
            }
            fprintf(file, "\\\\\n");
        }
    }
    closeTable(file, "Exchange Sort");
}

/**
Merge Sort:
Fix: it doesnt print well first steps
 */

void merge(FILE* file, char list[], int left, int middle, int right, int *row) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {

        L[i] = list[left + i];

        

    }
        
    for (j = 0; j < n2; j++){
        R[j] = list[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            list[k] = L[i];
            i++;
            

        } else {
            list[k] = R[j];
            j++;
        }
        k++;

        fprintf(file, "{\\bf %d} ", (*row)++);
        for (int t = 0; t < size; t++) {
            if (t == k - 1 || t == left || t == right || t == middle) {
                fprintf(file, "& \\X{%c} ", list[t]);
            } else {
                fprintf(file, "& \\C{%c} ", list[t]);
            }
        }
        fprintf(file, "\\\\\n");

        if (*row == 60) {
            closeTable(file, "Merge Sort");
            createTable(file, "Merge Sort (Continued)", list);
        }
    }

        
    

    while (i < n1) {
        list[k] = L[i];
        i++;
        k++;
        fprintf(file, "{\\bf %d} ", (*row)++);
        for (int t = 0; t < size; t++) {
            if (t == k || t == i) {
                fprintf(file, "& \\X{%c} ", list[t]);
            } else {
                fprintf(file, "& \\C{%c} ", list[t]);
            }
        }
        fprintf(file, "\\\\\n");
        if (*row == 60) {
            closeTable(file, "Merge Sort");
            createTable(file, "Merge Sort (Continued)", list);
        }
    }

    while (j < n2) {
        list[k] = R[j];
        j++;
        k++;
        fprintf(file, "{\\bf %d} ", (*row)++);
        for (int t = 0; t < size; t++) {
            if (t == k || t == j) {
                fprintf(file, "& \\X{%c} ", list[t]);
            } else {
                fprintf(file, "& \\C{%c} ", list[t]);
            }
        }
        fprintf(file, "\\\\\n");
        if (*row == 60) {
            closeTable(file, "Merge Sort");
            createTable(file, "Merge Sort (Continued)", list);
        }
    }
}

void mergeSort(FILE* file, char list[], int left, int right, int *row) {
    if (checkMerge < 1) {
        createTable(file, "Merge Sort", list);  
        checkMerge++;
    }

    if (left < right) {
        int middle = left + (right - left) / 2;

        
        mergeSort(file, list, left, middle, row);  
        mergeSort(file, list, middle + 1, right, row);

        merge(file, list, left, middle, right, row);
    }

    if (left == 0 && right == size - 1) {
        closeTable(file, "Merge Sort");
    }
}


/**
Quick Sort:
 */

 void swap(char* a, char* b) {
    char t = *a;
    *a = *b;
    *b = t;
}

int partition(FILE* file, char list[], int low, int high, int *row) {
  
    char pivot = list[high];
  
    int i = low - 1;


    for (int j = low; j <= high - 1; j++) {
        if (list[j] < pivot) {
            i++;
            swap(&list[i], &list[j]);
            fprintf(file, "{\\bf %d} ", (*row)++);
            for (int t = 0; t <= high; t++) {
                if (t == i || t == j || t == high) {
                    fprintf(file, "& \\X{%c} ", list[t]);
                } else {
                    fprintf(file, "& \\C{%c} ", list[t]);
                }
            }
            fprintf(file, "\\\\\n");
        }
    }
    
    swap(&list[i + 1], &list[high]);
    fprintf(file, "{\\bf %d} ", (*row)++);
    for (int t = 0; t < size; t++) {
        if (t == i + 1 || t == high) {
            fprintf(file, "& \\X{%c} ", list[t]);
        } else {
            fprintf(file, "& \\C{%c} ", list[t]);
        }
    }
    fprintf(file, "\\\\\n");
    return i + 1;
}

void quickSort(FILE* file, char list[], int low, int high, int *row) {
    if (checkQuick < 1) {
        createTable(file, "Quick Sort", list);  
        checkQuick++;
    }
    if (low < high) {
      
        int partitionValue = partition(file, list, low, high, row);

        quickSort(file, list, low, partitionValue - 1, row);
        quickSort(file, list, partitionValue + 1, high, row);
    }

    if (low == 0 && high == size - 1) {
        closeTable(file, "Quick Sort");
    }
}

/**
Shell Sort:

Improves on insertion sort by comparing elements separated by 
a gap rather than adjacent elements. Initially, the gap is large and is reduced 
progressively until it becomes 1. Elements are sorted within each gap interval, 
and the algorithm performs multiple passes to sort the entire list. This reduces 
the number of comparisons and swaps, making Shell Sort more efficient than simple 
insertion sort for larger lists.
 */
void shellSort(FILE* file, char list[], int size) {
    int row = 0;
    createTable(file, "Shell Sort", list); 

    for (int gap = size / 2; gap > 0; gap /= 2) {

        for (int i = gap; i < size; i++) {

            char temp = list[i];
            int j;

            for (j = i; j >= gap && list[j - gap] > temp; j -= gap) {

                list[j] = list[j - gap];

                fprintf(file, "{\\bf %d} ", row);
                for (int k = 0; k < size; k++) {
                    if (k == j || k == i) {
                        fprintf(file, "& \\X{%c} ", list[k]);
                    } else {
                        fprintf(file, "& \\C{%c} ", list[k]);
                    }
                }
                fprintf(file, "\\\\\n");
            }

            list[j] = temp;

            fprintf(file, "{\\bf %d} ", row++);
            for (int k = 0; k < size; k++) {
                if (k == j || k == i) {
                    fprintf(file, "& \\X{%c} ", list[k]);
                } else {
                    fprintf(file, "& \\C{%c} ", list[k]);
                }
            }
            fprintf(file, "\\\\\n");
            if (row == 24) {
                closeTable(file, "Shell Sort");
                createTable(file, "Shell Sort", list);
            }

        }
    }

    closeTable(file, "Shell Sort");
}

/**
Gnome Sort:

A simple comparison-based sorting algorithm 
similar to insertion sort but using a different approach. It 
iterates through the list by comparing adjacent elements and 
swaps them if they are out of order. When a swap is made, the algorithm 
moves back to the previous element (like a gnome moving backward in a line of 
unsorted flowers). This process continues until the array is sorted.
 */
 void gnomeSort(FILE* file, char list[]) {
    
    createTable(file, "Gnome Sort", list);
    int row = 0;
    int index = 0;

    while (index < size) {
        if (index == 0 || list[index] >= list[index - 1]) {
            fprintf(file, "{\\bf %d} ", row++);
            for (int k = 0; k < size; k++) {
                if (k == index || k == index - 1) {
                fprintf(file, "& \\X{%c} ", list[k]);
                } else {
                    fprintf(file, "& \\C{%c} ", list[k]);
                }
            }   
            fprintf(file, "\\\\\n");
            index++;
        } else {
            fprintf(file, "{\\bf %d} ", row);
            for (int k = 0; k < size; k++) {
                if (k == index || k == index - 1) {
                fprintf(file, "& \\X{%c} ", list[k]);
                } else {
                    fprintf(file, "& \\C{%c} ", list[k]);
                }
            }   
            fprintf(file, "\\\\\n");
            char temp = list[index];
            list[index] = list[index - 1];
            list[index - 1] = temp;

            fprintf(file, "{\\bf %d} ", row++);
            for (int k = 0; k < size; k++) {
                if (k == index || k == index - 1) {
                fprintf(file, "& \\X{%c} ", list[k]);
                } else {
                    fprintf(file, "& \\C{%c} ", list[k]);
                }
            }   
            fprintf(file, "\\\\\n");

            index--;

        }
            if (row % 50 == 0 && row != 0) {
                closeTable(file, "Gnome Sort");
                createTable(file, "Gnome Sort", list);
            }
    }

    closeTable(file, "Gnome Sort");
}

/*
Cocktail Sort:

An extension of the Bubble Sort algorithm that works by traversing the array in 
both directions alternately. It repeatedly passes through the array, first from 
left to right, moving the largest element to the end, and then from right to left, 
moving the smallest element to the beginning. This bidirectional movement allows 
Cocktail Sort to handle certain types of partially sorted data more efficiently 
than Bubble Sort.
*/
void cocktailSort(FILE* file, char list[]) {

    bool swapped = true;
    int start = 0;
    int end = size - 1;
    int row = 0;
    createTable(file, "Cocktail Sort", list);

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; i++) {
            
            if (list[i] > list[i + 1]) {
                fprintf(file, "{\\bf %d} ", row);
                for (int k = 0; k < size; k++) {
                    if (k == i || k == i + 1) {
                        fprintf(file, "& \\X{%c} ", list[k]);
                    } else {
                       fprintf(file, "& \\C{%c} ", list[k]);
                    }
                }
                fprintf(file, "\\\\\n");


                char temp = list[i];
                list[i] = list[i + 1];
                list[i + 1] = temp;
                swapped = true;

                fprintf(file, "{\\bf %d} ", row);
                for (int k = 0; k < size; k++) {
                    if (k == i || k == i + 1) {
                        fprintf(file, "& \\X{%c} ", list[k]);
                    } else {
                       fprintf(file, "& \\C{%c} ", list[k]);
                    }
                }
                fprintf(file, "\\\\\n");
            }

            if (row % 20 == 0 && row != 0) {
                closeTable(file, "Cocktail Sort");
                createTable(file, "Cocktail Sort", list);
            }
            fprintf(file, "{\\bf %d} ", row++);
            for (int k = 0; k < size; k++) {
                if (k == i || k == i + 1) {
                    fprintf(file, "& \\X{%c} ", list[k]);
                } else {
                    fprintf(file, "& \\C{%c} ", list[k]);
                }
            }
            fprintf(file, "\\\\\n");

            
        }

        if (!swapped) break;

        swapped = false;

        end--;

        for (int i = end - 1; i >= start; i--) {
            if (list[i] > list[i + 1]) {

                fprintf(file, "{\\bf %d} ", row);
                for (int k = 0; k < size; k++) {
                    if (k == i || k == i + 1) {
                        fprintf(file, "& \\X{%c} ", list[k]);
                    } else {
                       fprintf(file, "& \\C{%c} ", list[k]);
                    }
                }
                fprintf(file, "\\\\\n");

                char temp = list[i];
                list[i] = list[i + 1];
                list[i + 1] = temp;
                swapped = true;

                fprintf(file, "{\\bf %d} ", row);
                for (int k = 0; k < size; k++) {
                    if (k == i || k == i + 1) {
                        fprintf(file, "& \\X{%c} ", list[k]);
                    } else {
                       fprintf(file, "& \\C{%c} ", list[k]);
                    }
                }
                fprintf(file, "\\\\\n");
            }

            if (row % 20 == 0 && row != 0) {
                closeTable(file, "Cocktail Sort");
                createTable(file, "Cocktail Sort", list);
            }
            fprintf(file, "{\\bf %d} ", row++);
            for (int k = 0; k < size; k++) {
                if (k == i || k == i + 1) {
                    fprintf(file, "& \\X{%c} ", list[k]);
                } else {
                    fprintf(file, "& \\C{%c} ", list[k]);
                }
            }
            fprintf(file, "\\\\\n");
        }

        start++;
    }

    closeTable(file, "Cocktail Sort");
}

/*
Stooge Sort
*/
void stoogeSort(FILE* file, char list[], int start, int end, int* row) {
    
    if(checkStooge < 1) {
        createTable(file, "Stooge Sort", list);
        checkStooge++;
    }
    if (list[start] > list[end]) {
        char temp = list[start];
        list[start] = list[end];
        list[end] = temp;
    }

    fprintf(file, "{\\bf %d} ", (*row)++);  // Número de la fila en negrita
        for (int i = 0; i < size; i++) {
            if (i == start || i == end) {
                // Mostrar en rojo los elementos intercambiados
                fprintf(file, "& \\X{%c} ", list[i]);
            } else {
                // Mostrar en azul los demás elementos
                fprintf(file, "& \\C{%c} ", list[i]);
            }
        }
        fprintf(file, "\\\\\n");

        // Si hemos alcanzado 60 filas, cerrar y abrir una nueva tabla
        if (*row % 60 == 0) {
            closeTable(file, "Stooge Sort");
            createTable(file, "Stooge Sort (Continued)", list);
        
        }
    if (end - start + 1 > 2) {
        int t = (end - start + 1) / 3;
        stoogeSort(file, list, start, end - t, row);
        stoogeSort(file, list, start + t, end, row);
        stoogeSort(file, list, start, end - t, row);
    }
    if (start == 0 && end == size - 1) {
        closeTable(file, "Stooge Sort");
    }
}




// format:
// {\bf 01}& \X{D} & \X{L} & \C{Q} & \C{F} & \C{D} & \C{R} & \C{N} & \C{Q} & \C{S} & \C{D} & \C{W} & \C{A} & \C{L} & \C{O} & \C{K} & \C{D}\\
// {\\bf %d}
// & \\C{%c}
// & \\X{%c}