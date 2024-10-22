#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Programar N_Queens
// Programar MC_Queen

long double solutions = 0;
long double nodes = 1;
long double promisingNodes = 1;
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
 
    return segura; //no conflicts
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
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    } else if (argc > 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int max = atoi(argv[1]);

    printf("%-8s | %-15s | %-15s | %-15s | %-15s | %s\n", 
           "N", "Exhaustive", "Factorial", "Nodes", "Promising Nodes", "Solutions");
    
    for (int n = 4; n <= max; n++) {
        solutions = 0;
        nodes = 1;
        promisingNodes = 1;
        printf("-----------------------------------------------------------------------------------------------\n");


        // columns= qntQueens, exh, fact, back, prom, sol
        if (n < 9) {
            printf("%-8d |", n);                                      // For "N"
            printf(" %-15.0Lf |", exhaustive_NQueens(n));               // For "Exhaustive" (rounded to 0 decimal places)
            printf(" %-15.0Lf |", factorial_NQueens(n));                // For "Factorial" (rounded to 0 decimal places)
            NQueens(1, n);
            printf(" %-15.0Lf |", nodes);                               // For "Nodes" (rounded to 0 decimal places)
            printf(" %-15.0Lf |", promisingNodes);                      // For "Promising Nodes" (rounded to 0 decimal places)
            printf(" %.0Lf\n", solutions);                              // For "Solutions" (rounded to 0 decimal places)
        } else if (n < 16 && n >= 9) {
            printf("%-8d |", n);
            printf(" %-15.2e |", (double)exhaustive_NQueens(n));
            printf(" %-15.2e |", (double)factorial_NQueens(n));
            NQueens(1, n);
            printf(" %-15.2e |", (double)nodes);
            printf(" %-15.2e |", (double)promisingNodes);
            printf(" %.0Lf\n", solutions); 
            
        } else {
            printf("%-8d |", n);  
            printf(" %-15.2e |", (double)exhaustive_NQueens(n));
            printf(" %-15.2e |", (double)factorial_NQueens(n));
            printf(" %-15s |", "----"); 
            printf(" %-15s |", "----"); 
            printf(" %s\n", "----"); 
        }

    }
    return 0;
}