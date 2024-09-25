#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void processFile(char *filename, int frecuencyArray[]) {

}

// crea un archivo con el nombre <filename> y escribe la tabla de frecuencias
void createFile(char *filename) {
    FILE *file;
    file = fopen(filename, "w");
    fprintf(file, "Hex | Symbol | Frecuency");
    for (int i=0; i<256;i++) {
        fprintf(file, "\n%3x |", i);
        if (i < 32 || i == 127) {
            fprintf(file, "        |");
        } else {
            fprintf(file, "   %c    |", i);
        }
    }
    fclose(file);
}

// imprime el contenido de un archivo <file>
void printContent(FILE *file) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

// ./main <file-frec> <file-1> <file-2> ... <file-n>
int main(int argc, char* argv[]) {

    if (argc == 1) {
        // no se recibio ningun archivo
        printf("No se ingreso un archivo para ejecutar el programa\n");
        return 0;
    }

    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL) {
        // si no existe <file-frec>, lo crea
        createFile(argv[1]);
    }

    if (argc == 2) {
        // se recibe solamente <file-frec>
        // mostrar contenido
        file = fopen(argv[1], "r");
        printContent(file);
        printf("\n");
        return 0;
    }

    // array para tener el conteo de cada frecuencia
    int frecuency[256] = {0};

    for (int i=2; i<argc; i++) {
        printf("%s\n", argv[i]);
        processFile(argv[i], frecuency);
    } 


    return 0;
}