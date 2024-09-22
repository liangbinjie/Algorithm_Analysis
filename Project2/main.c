#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void processFile() {

}

void createFile(char *filename) {
    FILE *file;
    file = fopen(filename, "w");
    fprintf(file, "Hex | Symbol | Frecuency");
    for (int i=0; i<256;i++) {
        fprintf(file, "\n%3x |", i);
        if (i < 32 || i > 125) {
            fprintf(file, "        |");
        } else {
            fprintf(file, "   %c    |", i);
        }

    }
    fclose(file);
}

void printContent(FILE *file) {
    char c;
    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
    }
    fclose(file);
}

// ./main <file-frec> <file-1> <file-2> ... <file-n>
int main(int argc, char* argv[]) {
    if (argc == 1) {
        // no se recibio ningun archivo
        printf("No se ingreso un archivo para ejecutar el programa");
        return 0;
    }

    FILE *file;
    file = fopen(argv[1], "r");

    if (file == NULL) {
        // si no existe <file-frec>, lo crea
        fclose(file);
    }

    createFile(argv[1]);

    if (argc == 2) {
        // se recibe solamente <file-frec>
        // mostrar contenido
        file = fopen(argv[1], "r");
        printContent(file);
        return 0;
    }

    for (int i=2; i<argc; i++) {
        printf(argv[i]);
    } 
    return 0;
}