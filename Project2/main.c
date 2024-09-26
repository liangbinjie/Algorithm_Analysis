#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void processFile(char *filename, int frecuencyArray[]) {
    FILE *file;
    file = fopen(filename, "rb");
    unsigned char byte;
    while (fread(&byte, 1, 1, file)) {
        
        frecuencyArray[byte]++;

        if (byte >= 32 && byte <= 126) {  
            printf("Carácter: '%c' | En ASCII: %d (0x%x)\n", byte, byte, byte);
        } else {
            printf("No es imprimible | En ASCII: %d (0x%x)\n", byte, byte);
        }
    }

    fclose(file);

}

// crea un archivo con el nombre <filename> y escribe la tabla de frecuencias
void createFile(char *filename, int frecuencyArray[]) {
    FILE *file;
    file = fopen(filename, "w");
    fprintf(file, "Hex | Symbol | Frecuency");
    for (int i = 0; i < 256; i++) {
        fprintf(file, "%3x |", i);  // Imprime el valor en hexadecimal

        // Imprime el símbolo solo si es imprimible, de lo contrario deja un espacio vacío
        if (i < 32 || i == 127) {
            fprintf(file, "        |");  // Caracteres no imprimibles
        } else {
            fprintf(file, "   %c    |", i);  // Caracteres imprimibles
        }

        // Imprime la frecuencia
        fprintf(file, "   %d\n", frecuencyArray[i]);
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
        createFile(argv[1], frecuency);
    }

    if (argc == 2) {
        // se recibe solamente <file-frec>
        // mostrar contenido
        file = fopen(argv[1], "r");
        printContent(file);
        printf("\n");
        return 0;
    }

    

    for (int i=2; i<argc; i++) {
        printf("%s\n", argv[i]);
        processFile(argv[i], frecuency);
        createFile(argv[1], frecuency);
    } 


    return 0;
}