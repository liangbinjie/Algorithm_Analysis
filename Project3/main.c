#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

void saveCode(int frecuencyArray[], char *headerFile) {
    // Contar el número de símbolos con frecuencia > 0
    int uniqueSymbolsCount = 0;
    for (int i = 0; i < 256; i++) {
        if (frecuencyArray[i] > 0) {
            uniqueSymbolsCount++;
        }
    }

    char symbols[uniqueSymbolsCount];
    int freq[uniqueSymbolsCount];
    int index = 0;

    for (int i = 0; i < 256; i++) {
        if (frecuencyArray[i] > 0) {
            symbols[index] = (char)i;
            freq[index] = frecuencyArray[i];
            index++;
        }
    }

    int size = uniqueSymbolsCount;
    char *codes[uniqueSymbolsCount];

    for (int i = 0; i < uniqueSymbolsCount; i++) {
        codes[i] = NULL;
    }

    HuffmanCodes(symbols, freq, size, codes);

    FILE *file;
    file = fopen(headerFile, "w");

    fprintf(file, "#ifndef HUFFMAN_CODES_H\n");
    fprintf(file, "#define HUFFMAN_CODES_H\n\n");

    fprintf(file, "typedef struct {\n");
    fprintf(file, "    char symbol;\n");
    fprintf(file, "    char *code;\n");
    fprintf(file, "} HuffmanCode;\n\n");

    fprintf(file, "HuffmanCode huffmanCodes[] = {\n");

    // Escribimos los símbolos y sus códigos en el archivo .h
    for (int i = 0; i < size; i++) {
        fprintf(file, "    { '%c', \"%s\" },\n", symbols[i], codes[i]);
    }

    fprintf(file, "};\n\n");
    fprintf(file, "#endif // HUFFMAN_CODES_H\n");

    fclose(file);

    // Liberar memoria de los códigos
    for (int i = 0; i < size; i++) {
        free(codes[i]);
    }
}


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

    saveCode(frecuency, "huffman_codes.h");

    return 0;
}