#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"


void saveCode(int frecuencyArray[], char *headerFile1) {
    // Contar el número de símbolos con frecuencia > 0
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

    fprintf(codesFile, "HuffmanCode huffmanCodes[] = {\n");

    // Write symbols and their codes
    for (int i = 0; i < size; i++) {
        fprintf(codesFile, "    { '%c', \"%s\" },\n", symbols[i], codes[i]);
    }

    fprintf(codesFile, "};\n\n");
    fprintf(codesFile, "#endif // HUFFMAN_CODES_H\n");

    fclose(codesFile);

    // Liberar memoria de los códigos
    for (int i = 0; i < size; i++) {
        free(codes[i]);
    }
}



// procesa un archivo <filename> y llena el array <frecuencyArray> con las frecuencias de cada byte
// cierra el archivo despues de procesarlo
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

// ./main <file-frec> <file-1> <file-2> ... <file-n>
int main(int argc, char* argv[]) {
    // array para tener el conteo de cada frecuencia
    FILE *file;

    int frequencyArray[256] = {0};
    int frequency;
    char buffer[256];
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

    // si se recibe solamente <file-frec> y existe
    // mostrar contenido
    if (file != NULL && argc == 2) {
        file = fopen(argv[1], "r");
        printContent(file);
        
        //saveCode(frequencyArray, "huffman_codes.h");
        printf("\n");
    }

    // si no ocurre ninguno de los casos anteriores
    // procesar toda la lista de archivos
    
    if (file != NULL) {
        // extraemos las frecuencias del archivo
        int i = 0;
        fgets(buffer, sizeof(buffer), file);
        while (fgets(buffer, sizeof(buffer), file)) {
            if (sscanf(buffer, " %*x | %*s | %d", &frequency) == 1) {
                frequencyArray[i] = frequency;
            }
            i++;
        }
    }

    // procesar los archivos
    for (int i=2; i<argc; i++) {
        processFile(argv[i], frequencyArray);
    } 
    
    // crear archivo con la tabla de frecuencias
    createFile(argv[1], frequencyArray);
    file = fopen(argv[1], "r");
    printContent(file);
    printf("\n");
    printf("WWWW");
    saveCode(frequencyArray, "huffman_codes.h");

    return 0;
}