#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int num1[4] = {0,0,0,0};
int num2[4] = {0,0,0,0};


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

void printList(int *list) {
    for (int i = 0; i < 4; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int main() {   
    srand(time(0));

    for (int i = 0; i < 4; i++) {
        num1[i] = rand() % 1000;
        num2[i] = rand() % 1000;
    }


    clock_t begin = clock();
    /* here, do your time-consuming job */
    for (int fila=0;fila<4;fila++) {
        for (int columna=0;columna<4;columna++) {
            printf("%d * %d = %d\n", num1[fila], num2[columna], multiplicar(num1[fila], num2[columna]));
        }
        printf("\n");
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f\n", time_spent);

    begin = clock();
    for (int fila=0;fila<4;fila++) {
        for (int columna=0;columna<4;columna++) {
            printf("%d * %d = %d\n", num2[fila], num1[columna], multiplicar(num2[fila], num1[columna]));
        }
        printf("\n");
    }
    
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f\n", time_spent);
    
    printList(num1);
    printList(num2);


    return 0;
}



