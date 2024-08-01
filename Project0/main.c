#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Global variables
int N = 50000;
int num1[4] = {0,0,0,0};
int num2[4] = {0,0,0,0};

// ASM Functions
int standardMulASM(int a, int b);
int russianMulASM(int a, int b);
int nullMulASM(int a, int b);

// C Functions

/**
 * @brief Multiplies two integers.
 *
 * This function takes two integers as input and returns their product.
 *
 * @param[in] a The first integer to be multiplied.
 * @param[in] b The second integer to be multiplied.
 * @return The product of the two integers.
 */
int standardMul(int a, int b) {
    return a * b;
}

/**
 * @brief Empty function.
 *
 * This function takes two integers as input and returns 0.
 *
 * @param[in] a The first integer to receive.
 * @param[in] b The second integer to receive.
 * @return 0.
 */
int nullMul(int a, int b) {
    return 0;
}

/**
 * @brief Russian Multiplication.
 *
 * This function takes two integers as input and returns the product of the two
 * using the Russian multiplication method.
 *
 * @param[in] a The first integer to receive.
 * @param[in] b The second integer to receive.
 * @return The product of the two integers.
 */
int russianMul(int a, int b) {
    int resultado = 0; // Initialize the result to 0

    while (b > 0) { // Continue until b becomes 0
        if (b & 1) { // If the least significant bit of b is 1
            resultado += a; // Add the current value of a to the result
        }
        a <<= 1; // Double the value of a (equivalent to a = a * 2)
        b >>= 1; // Halve the value of b (equivalent to b = b / 2)
    }
    return resultado; // Return the final result
}

/**
 * @brief Main function that generates the timestamps.
 *
 * This function prints the tables using the different versions of multiplication, using 
 * random numbers and multiplying them N times. It measures the time it takes to complete 
 * the operations in each version.
 *
 * @return 0.
 */
int main() {
    double time_spentInd = 0.0;
    double time_multplications = 0.0;
    double time_spentTable = 0.0;

    srand(time(0));                 // seed generation

    for (int i = 0; i < 4; i++) {   // assign random numbers to the table
        num1[i] = rand() % 10000;
        num2[i] = rand() % 10000;
    }

    printf("N: %d\n", N);

    clock_t begin = clock();
    printf("nullMul(A * B)\n");
    printf("          |");

    // Print column headers
    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num2[columna]);
    }
    printf("\n");

    // Measure and print the time taken for nullMul in A * B order
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
            printf(" %4d * %4d = %8d / %2.2f ms |", num1[fila], num2[columna], nullMul(num1[fila], num2[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying A * B returning 0 in C: %2.3f ms\n", time_multplications);


    time_multplications = 0.0;


    printf("\nnullMul(B * A)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num1[columna]);
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
            printf(" %4d * %4d = %8d / %2.2f ms |", num2[fila], num1[columna], nullMul(num2[fila], num1[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying B * A returning 0 in C: %2.3f ms\n", time_multplications);

    clock_t end = clock();
    time_spentTable = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
    printf("\nExecution time taken from both tables: %2.3f ms\n\n", time_spentTable);

    time_multplications = 0.0;


    printf("nullMulASM(A * B)\n");
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
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                nullMulASM(num1[fila], num2[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %4d * %4d = %8d / %2.2f ms |", num1[fila], num2[columna], nullMulASM(num1[fila], num2[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying A * B returning 0 in ASM: %2.3f ms\n", time_multplications);

    time_multplications = 0.0;


    printf("\nnullMulASM(B * A)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num1[columna]);
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
            printf(" %4d * %4d = %8d / %2.2f ms |", num2[fila], num1[columna], nullMulASM(num2[fila], num1[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying B * A returning 0 in ASM: %2.3f ms\n", time_multplications);
    
    end = clock();
    time_spentTable = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
    printf("\nExecution time taken from both tables: %2.3f ms\n\n", time_spentTable);

    getc(stdin);

    // Standard Multiplication =================================================================================================

    time_multplications = 0.0;

    begin = clock();
    printf("standardMul(A * B)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num2[columna]);
    }
    printf("\n");
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num1[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                standardMul(num1[fila], num2[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %4d * %4d = %8d / %2.2f ms |", num1[fila], num2[columna], standardMul(num1[fila], num2[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying A * B using standard method in C: %2.3f ms\n", time_multplications);


    time_multplications = 0.0;


    printf("\nstandardMul(B * A)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num1[columna]);
    }
    printf("\n");
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num2[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                standardMul(num2[fila], num1[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %4d * %4d = %8d / %2.2f ms |", num2[fila], num1[columna], standardMul(num2[fila], num1[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying B * A using standard method in C: %2.3f ms\n", time_multplications);

    end = clock();
    time_spentTable = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
    printf("\nExecution time taken from both tables: %2.3f ms\n\n", time_spentTable);

    time_multplications = 0.0;

    printf("standardMulASM(A * B)\n");
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
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                standardMulASM(num1[fila], num2[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %4d * %4d = %8d / %2.2f ms |", num1[fila], num2[columna], standardMulASM(num1[fila], num2[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying A * B using standard method in ASM: %2.3f ms\n", time_multplications);


    time_multplications = 0.0;


    printf("\nstandardMulASM(B * A)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num1[columna]);
    }
    printf("\n");
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num2[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                standardMulASM(num2[fila], num1[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %4d * %4d = %8d / %2.2f ms |", num2[fila], num1[columna], standardMulASM(num2[fila], num1[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying B * A using standard method in ASM: %2.3f ms\n", time_multplications);
    
    end = clock();
    time_spentTable = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
    printf("\nExecution time taken from both tables: %2.3f ms\n\n", time_spentTable);


    getc(stdin);
    // Russian Multiplication =================================================================================================

    time_multplications = 0.0;

    begin = clock();
    printf("russianMul(A * B)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num2[columna]);
    }
    printf("\n");
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num1[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                russianMul(num1[fila], num2[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %4d * %4d = %8d / %2.2f ms |", num1[fila], num2[columna], russianMul(num1[fila], num2[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying A * B using russian method in C: %2.3f ms\n", time_multplications);


    time_multplications = 0.0;


    printf("\nrussianMul(B * A)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num1[columna]);
    }
    printf("\n");
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num2[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                russianMul(num2[fila], num1[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %4d * %4d = %8d / %2.2f ms |", num2[fila], num1[columna], russianMul(num2[fila], num1[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying B * A using russian method in C: %2.3f ms\n", time_multplications);

    end = clock();
    time_spentTable = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
    printf("\nExecution time taken from both tables: %2.3f ms\n\n", time_spentTable);

    time_multplications = 0.0;

    printf("russianMulASM(A * B)\n");
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
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                russianMulASM(num1[fila], num2[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %4d * %4d = %8d / %2.2f ms |", num1[fila], num2[columna], russianMulASM(num1[fila], num2[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying A * B using russian method in ASM: %2.3f ms\n", time_multplications);


    time_multplications = 0.0;


    printf("\nrussianMulASM(B * A)\n");
    printf("          |");

    for (int columna = 0; columna < 4; columna++) {
        printf("%35d|", num1[columna]);
    }
    printf("\n");
    for (int fila = 0; fila < 4; fila++) {
        printf("%-10d|", num2[fila]);
        for (int columna = 0; columna < 4; columna++) {
            time_spentInd = 0.0; 
            for (int i = 0; i < N; i++) {
                clock_t beginInd = clock();
                russianMul(num2[fila], num1[columna]);
                clock_t endInd = clock();
                time_spentInd += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
                time_multplications += (double)(endInd - beginInd) / (CLOCKS_PER_SEC / 1000);
            }
            printf(" %4d * %4d = %8d / %2.2f ms |", num2[fila], num1[columna], russianMul(num2[fila], num1[columna]), time_spentInd);
        }
        printf("\n");
    }
    printf("\nExecution time multiplying B * A using russian method in ASM: %2.3f ms\n", time_multplications);
    
    end = clock();
    time_spentTable = (double)(end - begin) / (CLOCKS_PER_SEC / 1000);
    printf("\nExecution time taken from both tables: %2.3f ms\n\n", time_spentTable);

    return 0;

}