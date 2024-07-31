#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Variables globales
int times = 100000;
int num1[4] = {0,0,0,0};
int num2[4] = {0,0,0,0};

// Declaración de funciones en ASM
int standardMulASM(int a, int b);

int russianMulASM(int a, int b);

int nullMulASM(int a, int b);

// Declaración de funciones en C
int multiplicar(int a, int b) {
    return a * b;
}

int multiplicarVacio(int a, int b) {
    return 0;
}

int multiplicarAntiguo(int a, int b) {
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
    srand(time(0));                         // genera la seed

    for (int i = 0; i < 4; i++) {           // asignar numero randoms a la tabla
        num1[i] = rand() % 1000;
        num2[i] = rand() % 1000;
    }

    double time_spentInd = 0.0;
    double time_spentTable = 0.0;
    printf("Versión Vacía A * B\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num2[columna]);
    }
    printf("\n");
    clock_t begin = clock();
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num1[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int timesToLoop = 0; timesToLoop < times; timesToLoop++){
                clock_t beginIndividual = clock();
                multiplicarVacio(num1[fila], num2[columna]);
                clock_t endIndividual = clock(); 
                time_spentInd += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;
                time_spentTable += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;

            }
            printf(" %3d * %3d = %6d / %2.10f |", num1[fila], num2[columna], multiplicarVacio(num1[fila], num2[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nTiempo de ejecución en el orden A * B de la versión vacía: %f\n", time_spentTable);

    printf("\nVersión Vacía B * A\n");
    printf("          |");
    time_spentTable = 0.0;
    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num1[columna]);
    }
    printf("\n");

    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num2[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int timesToLoop = 0; timesToLoop < times; timesToLoop++){
                clock_t beginIndividual = clock();
                multiplicarVacio(num2[fila], num1[columna]);
                clock_t endIndividual = clock(); 
                time_spentInd += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;
                time_spentTable += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;
            }
            printf(" %3d * %3d = %6d / %2.10f |", num2[fila], num1[columna], multiplicarVacio(num2[fila], num1[columna]), time_spentInd);
        }
        printf("\n");
    }

    printf("\nTiempo de ejecución en el orden B * A de la versión vacía: %f\n", time_spentTable);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion total de la versión vacía: %f\n", time_spent);

    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");

    time_spentInd = 0.0;
    time_spent = 0.0;
    time_spentTable = 0.0;

    printf("Versión Estandár A * B\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num2[columna]);
    }
    printf("\n");

    begin = clock();
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num1[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int timesToLoop = 0; timesToLoop < times; timesToLoop++){
                clock_t beginIndividual = clock();
                multiplicar(num1[fila], num2[columna]);
                clock_t endIndividual = clock(); 
                time_spentInd += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;
                time_spentTable += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;
            }
            printf(" %3d * %3d = %6d / %2.10f |", num1[fila], num2[columna], multiplicar(num1[fila], num2[columna]), time_spentInd);
        }
        printf("\n");
    }

    printf("\nTiempo de ejecución en el orden A * B de la versión normal: %f\n", time_spentTable);

    printf("\nVersión Estandár B * A\n");
    printf("          |");
    time_spentTable = 0.0;
    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num1[columna]);
    }
    printf("\n");

    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num2[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int timesToLoop = 0; timesToLoop < times; timesToLoop++){
                clock_t beginIndividual = clock();
                multiplicar(num2[fila], num1[columna]);
                clock_t endIndividual = clock(); 
                time_spentInd += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;
                time_spentTable += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;
            }
            printf(" %3d * %3d = %6d / %2.10f |", num2[fila], num1[columna], multiplicar(num2[fila], num1[columna]), time_spentInd);
        }
        printf("\n");
    }

    printf("\nTiempo de ejecución en el orden B * A de la versión normal: %f\n", time_spentTable);

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion total de la versión normal: %f\n", time_spent);

    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");

    time_spentInd = 0.0;
    time_spent = 0.0;
    time_spentTable = 0.0;

    printf("Versión Antigua A * B\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num2[columna]);
    }
    printf("\n");

    begin = clock();
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num1[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int timesToLoop = 0; timesToLoop < times; timesToLoop++){
                clock_t beginIndividual = clock();
                multiplicarAntiguo(num1[fila], num2[columna]);
                clock_t endIndividual = clock(); 
                time_spentInd += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;
                time_spentTable += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;
            }
            printf(" %3d * %3d = %6d / %2.10f |", num1[fila], num2[columna], multiplicarAntiguo(num1[fila], num2[columna]), time_spentInd);
        }
        printf("\n");
    }

    printf("\nTiempo de ejecución en el orden A * B de la versión antigua: %f\n", time_spentTable);

    printf("\nVersión Antigua B * A\n");
    printf("          |");
    time_spentTable = 0.0;
    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num1[columna]);
    }
    printf("\n");

    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num2[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int timesToLoop = 0; timesToLoop < times; timesToLoop++){
                clock_t beginIndividual = clock();
                multiplicarAntiguo(num2[fila], num1[columna]);
                clock_t endIndividual = clock(); 
                time_spentInd += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;
                time_spentTable += (double)(endIndividual - beginIndividual) / CLOCKS_PER_SEC;
            }
            printf(" %3d * %3d = %6d / %2.10f |", num2[fila], num1[columna], multiplicarAntiguo(num2[fila], num1[columna]), time_spentInd);
        }
        printf("\n");
    }

    printf("\nTiempo de ejecución en el orden B * A de la versión antigua: %f\n", time_spentTable);

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion total de la versión antigua: %f\n", time_spent);

    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");

    return 0;
}