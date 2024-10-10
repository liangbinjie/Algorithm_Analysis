#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"
#define ARRAY_SIZE 256


void saveCode(int frecuencyArray[], char *headerFile1) {
    int uniqueSymbolsCount = 0;
    for (int i = 0; i < 256; i++) {
        if (frecuencyArray[i] >= 0) {
            uniqueSymbolsCount++;
        }
    }

    char symbols[uniqueSymbolsCount];
    int freq[uniqueSymbolsCount];
    int index = 0;

    for (int i = 0; i < 256; i++) {
        if (frecuencyArray[i] >= 0) {
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

    HuffmanCodes(symbols, freq, size, codes, "huffman_tree.h");

    // Generate huffman_codes.h
    FILE *codesFile;
    codesFile = fopen(headerFile1, "w");

    fprintf(codesFile, "#ifndef HUFFMAN_CODES_H\n");
    fprintf(codesFile, "#define HUFFMAN_CODES_H\n\n");
    fprintf(codesFile, "typedef struct HuffmanCode {\n  unsigned char character;\n  char *code;\n} HuffmanCode;\n\n");

    fprintf(codesFile, "HuffmanCode huffmanCodes[] = {\n");

    for (int i = 0; i < size; i++) {
        fprintf(codesFile, "    { 0x%02x, \"%s\" },\n", (unsigned char)symbols[i], codes[i]);
    }

    fprintf(codesFile, "};\n\n");
    fprintf(codesFile, "#endif // HUFFMAN_CODES_H\n");

    fclose(codesFile);

    for (int i = 0; i < size; i++) {
        free(codes[i]);
    }
}

void processFile(char *filename, int frequencyArray[]) {
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }
    unsigned char byte;
    while (fread(&byte, 1, 1, file)) {
        frequencyArray[byte] += 1;
    }
    fclose(file);
}

// crea un archivo con el nombre <filename> y escribe la tabla de frecuencias
void createFile(char *filename, int frequencyArray[]) {
    
    FILE *file;
    file = fopen(filename, "w");
    fprintf(file, "Hex | Symbol | Frequency");
    for (int i = 0; i < 256; i++) {
        fprintf(file, "\n%3x |", i);  // Imprime el valor en hexadecimal

        // Imprime el símbolo solo si es imprimible, de lo contrario deja un espacio vacío
        if (i < 32 || i > 126) {
            fprintf(file, "        |");  // Caracteres no imprimibles
        } else {
            fprintf(file, "   %c    |", i);  // Caracteres imprimibles
        }

        // Imprime la frecuencia
        fprintf(file, " %d",frequencyArray[i]);
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

void saveFrequenciesToFile(char *filename, int frequencyArray[]) {
    FILE *file;
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s para escribir\n", filename);
        return;
    }

    fprintf(file, "Hex | Frequency\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (frequencyArray[i] > 0) {
            fprintf(file, "0x%02x | %d\n", i, frequencyArray[i]);
        }
    }

    fclose(file);
}

// ./main <file-frec>
int main(int argc, char* argv[]) {
    // array para tener el conteo de cada frecuencia
    FILE *file;
    int frequencyArray[256] = {0};
    int frequency;

    // si no se ingresa ningun archivo
    // se imprime un mensaje de error
    if (argc == 1) {
        printf("No se ingreso un archivo para ejecutar el programa\n");
        return 0;
    }

    file = fopen(argv[1], "r");

    // si el archivo no existe y no se tiene ingreso de archivos
    if (file == NULL && argc == 2) {
        printf("No existe el archivo\n");
        return 0;
    }
    
    if ( (file != NULL)|| (file != NULL && argc == 2) ) {
        // extraemos las frecuencias del archivo
        // int hexValue;

    // Leer la cabecera del archivo
    int index = 0;    // Contador para las posiciones en el array
    char buffer[256]; // Buffer para leer cada línea del archivo
    char *dataStart;  // Puntero para saltar los primeros 14 caracteres

    // Leer la cabecera del archivo
    fgets(buffer, sizeof(buffer), file); // Salta la primera línea (la cabecera)

    // Procesar cada línea del archivo
    while (fgets(buffer, sizeof(buffer), file)) {
        // Saltar los primeros 14 caracteres (para ignorar el símbolo)
        dataStart = buffer + 14;

        // Leer solo la frecuencia desde el carácter 14
        if (sscanf(dataStart, "%d", &frequency) == 1) {
            // Asignar la frecuencia a la posición actual del array
            frequencyArray[index] = frequency;

            // Mensaje de depuración
            printf("Índice: %d, Frecuencia: %d\n", index, frequency);

            // Incrementar el índice para la siguiente posición del array
            index++;

            // Verificamos que no nos pasemos del tamaño del array
            if (index > 255) {
                printf("Se ha alcanzado el límite del array.\n");
                break;
            }
        } else {
            // Mensaje de depuración para formato incorrecto
            printf("Formato incorrecto o frecuencia no válida: %s\n", buffer);
        }
    }

    }
    // procesar los archivos
    file = fopen(argv[1], "r");
    printContent(file);
    printf("\n");
    printf("Contenido del array: ");
    for (int i = 0; i < 256; i++) {
        printf("%d ", frequencyArray[i]);  // Imprimir el elemento actual
    }
    printf("\n");
    saveFrequenciesToFile("frequencies.txt", frequencyArray);
    saveCode(frequencyArray, "huffman_codes.h");
    return 0;
}