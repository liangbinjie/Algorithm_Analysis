#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// procesa un archivo <filename> y llena el array <frecuencyArray> con las frecuencias de cada byte
// cierra el archivo despues de procesarlo
void processFile(char *filename, int frecuencyArray[]) {
    FILE *file;
    file = fopen(filename, "rb");
    unsigned char byte;
    while (fread(&byte, 1, 1, file)) {
        frecuencyArray[byte]++;
    }

    fclose(file);

}

// retorna la suma de todas las frecuencias
int frecuencyTotal(int frecuencyArray[]) {
    int total = 0;
    for (int i = 0; i < 256; i++) {
        total += frecuencyArray[i];
    }
    return total;
}

// crea un archivo con el nombre <filename> y escribe la tabla de frecuencias
void createFile(char *filename, int frecuencyArray[], int total) {
    
    FILE *file;
    file = fopen(filename, "w");
    fprintf(file, "Hex | Symbol | Frecuency");
    for (int i = 0; i < 256; i++) {
        fprintf(file, "\n%3x |", i);  // Imprime el valor en hexadecimal

        // Imprime el símbolo solo si es imprimible, de lo contrario deja un espacio vacío
        if (i < 32 || i > 126) {
            fprintf(file, "        |");  // Caracteres no imprimibles
        } else {
            fprintf(file, "   %c    |", i);  // Caracteres imprimibles
        }

        // Imprime la frecuencia
        fprintf(file, " %f", (double)frecuencyArray[i]/total);
        // fprintf(file, " %f", (double)frecuencyArray[i])/1;
    }
    fclose(file);
}

// - Imprime el contenido de un archivo <file>
// - Cierra archivo despues de leerlo
void printContent(FILE *file) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

// ./main <file-frec> <file-1> <file-2> ... <file-n>
int main(int argc, char* argv[]) {
    // array para tener el conteo de cada frecuencia
    int frecuency[256] = {0};

    if (argc == 1) {
        // no se recibio ningun archivo
        printf("No se ingreso un archivo para ejecutar el programa\n");
        return 0;
    }

    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL) {
        // si no existe <file-frec>, lo crea
        createFile(argv[1], frecuency, 1);
    }

    if (argc == 2) {
        // se recibe solamente <file-frec>
        // mostrar contenido
        file = fopen(argv[1], "r");
        printContent(file);
        printf("\n");
        return 0;
    }

    // procesar todos la lista de archivos
    for (int i=2; i<argc; i++) {
        printf("%s\n", argv[i]);
        processFile(argv[i], frecuency);
    } 
    int total = frecuencyTotal(frecuency);
    createFile(argv[1], frecuency, total);
    file = fopen(argv[1], "r");
    printContent(file);
    printf("\n");

    return 0;
}