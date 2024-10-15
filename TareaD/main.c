#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Programar N_Queens
// Programar MC_Queen

void Queens(int n) {
    int j;
    if (promising(n)) {
        // escribir la solucion
    } else {
        for (j = 0; j < n; j++) {
            // col[n+1] = j;
            Queens(n+1);
        }
    }
}

double power(int base, int exp) {
    long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

double exhaustive_NQueens(int n) {
    return (power(n,n+1)-1)/(n-1);
}

double factorial_NQueens(int n) {
    double result = 1;
    for (int i = 1; i <= n; i++) {
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
    int n = atoi(argv[1]);
    if (n < 9) {
        printf("%ld\n", (long)exhaustive_NQueens(n));
        printf("%ld\n", (long)factorial_NQueens(n));
    } else {
        printf("%.2e\n", exhaustive_NQueens(n));
        printf("%.2e\n", factorial_NQueens(n));
    }
    return 0;

}
    