#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Global variables
int N = 100000;
int num1[4] = {0,0,0,0};
int num2[4] = {0,0,0,0};

// Declaración de funciones en ASM
int standardMulASM(int a, int b);

int russianMulASM(int a, int b);

int nullMulASM(int a, int b);

// Declaración de funciones en C
int standardMult(int a, int b) {
    return a * b;
}

int nullMul(int a, int b) {
    return 0;
}

int russianMul(int a, int b) {
    int resultado = 0;

    while (b > 0) {

        if (b & 1) {
            resultado += a;
        }

        a <<= 1;
        b >>= 1;
       
    }
    return resultado;
}


// Main function
int main() {
    double time_spentInd = 0.0;
    double time_multplications = 0.0;
    double time_spentTable = 0.0;

    srand(time(0));                 // seed generation

    for (int i = 0; i < 4; i++) {   // assign random numbers to the table
        num1[i] = rand() % 1000;
        num2[i] = rand() % 1000;
    }

    printf("nullMul(A * B)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%25d|", num2[columna]);
    }
    printf("\n");
    clock_t begin = clock();
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num1[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                nullMul(num1[fila], num2[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %3d * %3d = %2d / %2.3f |", num1[fila], num2[columna], nullMul(num1[fila], num2[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nTiempo de ejecución en el orden A * B de la versión vacía: %f ms\n", time_multplications);


    time_multplications = 0.0;


    printf("\nnullMul(B * A)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%25d|", num1[columna]);
    }
    printf("\n");
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num2[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                nullMul(num2[fila], num1[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %3d * %3d = %2d / %2.3f |", num2[fila], num1[columna], nullMul(num2[fila], num1[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nTiempo de ejecución en el orden B * A de la versión vacía: %f ms\n", time_multplications);

    clock_t end = clock();



    time_multplications = 0.0;

    printf("nullMulASM(A * B)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%25d|", num2[columna]);
    }
    printf("\n");

    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num1[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                nullMulASM(num1[fila], num2[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %3d * %3d = %2d / %2.3f |", num1[fila], num2[columna], nullMulASM(num1[fila], num2[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nTiempo de ejecución en el orden A * B de la versión vacía ASM: %f ms\n", time_multplications);


    time_multplications = 0.0;


    printf("\nnullMulASM(B * A)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%25d|", num1[columna]);
    }
    printf("\n");
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num2[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                nullMulASM(num2[fila], num1[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %3d * %3d = %2d / %2.3f |", num2[fila], num1[columna], nullMulASM(num2[fila], num1[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nTiempo de ejecución en el orden B * A de la versión vacía ASM: %f ms\n", time_multplications);


    return 0;

}