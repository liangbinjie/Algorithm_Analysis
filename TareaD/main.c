#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

long double solutions = 0;
long double nodes = 1;
long double promisingNodes = 1;
long double mc_nodes = 1;
int board[100];

int promising(int row,int column) {
    int i = 1;
    int segura = 1;
    while (segura && i < row ) {
        // Si se atacan por columna o diagonal
        if(board[i]==column || abs(board[i]-column)==abs(i-row)) {
            segura = 0;
        }
        i++;
    }
 
    return segura;
}

long double MC_Queens(int n) {
    int i, j, m;
    long double mprod, numnodes;
    bool prom_children[n]; 
    int promising_indices[n];

    i = 0;
    numnodes = 1;  // siempre se comienza con el nodo raíz
    m = 1;  // inicializar a 1 nodo promising para la raíz
    mprod = 1;  // producto de nodos promising

    while (m != 0 && i != n) {
        mprod = mprod * m;  // multiplicamos el número actual de nodos promising
        numnodes = numnodes + mprod * n;  // agregamos los nodos en este nivel

        i++;  // siguiente fila
        m = 0;  // resetear el número de nodos promising

        // prom?children = conjunto vacio
        for (j = 0; j < n; j++) {
            prom_children[j] = false;
        }

        int promising_count = 0;
        for (j = 1; j <= n; j++) {
            if (promising(i, j)) { 
                m++;  // incrementar el conteo de nodos prometedores
                prom_children[j - 1] = true;  // marcar esta columna como promising
                promising_indices[promising_count++] = j;  // almacenar la columna promising
            }
        }

        if (m != 0) {
            // selecionar aleatoriamente de los nodos promising
            int random_index = rand() % promising_count;
            j = promising_indices[random_index]; 
            board[i] = j; 
        }
    }
    return numnodes; 
}


void NQueens(int k, int n) {
    int i;
    for (i=1;i<=n;i++) {
        nodes++;
        if (promising(k, i)) {
            promisingNodes++;
            board[k] = i;
            if (k==n) {
                solutions++;
            } else {
                NQueens(k+1,n);
            }
        }
    }
}

long double power(int base, int exp) {
    long double result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

long double exhaustive_NQueens(int n) {
    return (power(n,n+1)-1)/(n-1);
}

long double factorial_NQueens(int n) {
    long double result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(int argc, char *argv[]) {
    // if (argc != 2) {
    //     printf("Usage: %s <n>\n", argv[0]);
    //     return 1;
    // } else if (argc > 2) {
    //     printf("Usage: %s <n>\n", argv[0]);
    //     return 1;
    // }

    // int max = atoi(argv[1]);

    FILE *file = fopen("output.txt", "w");


    srand(time(NULL));
    printf("%-8s | %-15s | %-15s | %-15s | %-15s | %-10s | %s\n", 
           "N", "Exhaustive", "Factorial", "Nodes", "Promising Nodes", "Solutions", "MC_Queens");
    for (int n = 4; n <= 100; n++) {
        solutions = 0;
        nodes = 1;
        promisingNodes = 1;
        printf("-----------------------------------------------------------------------------------------------------------------\n");

        for (int rep=1; rep<=1000; rep++) {
            mc_nodes += MC_Queens(n);
        }
        mc_nodes = mc_nodes/1000;
        // columns= qntQueens, exh, fact, back, prom, sol
        if (n < 9) {
            printf("%-8d |", n);                                      // For "N"
            printf(" %-15.0Lf |", exhaustive_NQueens(n));               // For "Exhaustive" (rounded to 0 decimal places)
            printf(" %-15.0Lf |", factorial_NQueens(n));                // For "Factorial" (rounded to 0 decimal places)
            NQueens(1, n);
            printf(" %-15.0Lf |", nodes);                               // For "Nodes" (rounded to 0 decimal places)
            printf(" %-15.0Lf |", promisingNodes);                      // For "Promising Nodes" (rounded to 0 decimal places)
            printf(" %-10.0Lf |", solutions);                              // For "Solutions" (rounded to 0 decimal places)
            printf(" %.Lf\n", mc_nodes);                                    // For "MC_Queens" (rounded to 0 decimal places)
        } else if (n < 16 && n >= 9) {
            printf("%-8d |", n);
            printf(" %-15.2e |", (double)exhaustive_NQueens(n));
            printf(" %-15.2e |", (double)factorial_NQueens(n));
            NQueens(1, n);
            printf(" %-15.2e |", (double)nodes);
            printf(" %-15.2e |", (double)promisingNodes);
            printf(" %-10.Lf |", solutions);                              // For "Solutions" (rounded to 0 decimal places)
            printf(" %.2e\n", (double)mc_nodes);  
            
        } else {
            printf("%-8d |", n);  
            printf(" %-15.2e |", (double)exhaustive_NQueens(n));
            printf(" %-15.2e |", (double)factorial_NQueens(n));
            printf(" %-15s |", "----"); 
            printf(" %-15s |", "----"); 
            printf(" %-10s |", "----");                              // For "Solutions" (rounded to 0 decimal places)
            printf(" %.2e\n", (double)mc_nodes);   
        }

    }
    return 0;
}