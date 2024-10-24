#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "huffman_codes.h"  

#define ARRAY_SIZE 256
//good

// Estructura para almacenar info de archivos
typedef struct {
    char filename[256];
    unsigned int originalSize;
    unsigned int compressedSize;
} FileInfo;

int compressFile(const char *filename, FileInfo *fileInfo);  // Now returns int to indicate success

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("No se ingresó un archivo para ejecutar el programa\n");
        return 0;
    }

    // Almacenar info de archivos procesados
    FileInfo fileInfos[argc - 1];
    int processedFileCount = 0;  // Keep track of valid files

    // Procesar cada archivo
    for (int i = 1; i < argc; i++) {
        if (compressFile(argv[i], &fileInfos[processedFileCount])) {
            processedFileCount++;  // Increment count only for valid files
        }
    }

    // Si no se procesó ningún archivo, mostrar un mensaje
    if (processedFileCount == 0) {
        printf("No se pudo procesar ningún archivo.\n");
        return 0;
    }

    // Mostrar tabla final de compactación
    printf("\nTabla de compactación:\n");
    printf("%-20s %-15s %-15s %-15s\n", "Archivo", "Tamaño original", "Tamaño comprimido", "Compactación");
    unsigned int totalOriginalSize = 0, totalCompressedSize = 0;
    for (int i = 0; i < processedFileCount; i++) {
        FileInfo info = fileInfos[i];
        totalOriginalSize += info.originalSize;
        totalCompressedSize += info.compressedSize;
        double compressionRatio = ((double)info.compressedSize / info.originalSize) * 100;
        printf("%-20s %-15u %-15u %-15.2f%%\n", info.filename, info.originalSize, info.compressedSize, 100 - compressionRatio);
    }
    
    // Gran total
    double totalCompressionRatio = ((double)totalCompressedSize / totalOriginalSize) * 100;
    printf("\nGran total: %u bytes -> %u bytes (%.2f%% compactación)\n", totalOriginalSize, totalCompressedSize, 100 - totalCompressionRatio);

    return 0;
}

// Retorna 1 si el archivo fue procesado correctamente, 0 si hubo un error
int compressFile(const char *filename, FileInfo *fileInfo) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No existe el archivo %s\n", filename);
        return 0;  // Return 0 to indicate failure
    }

    // Crear el nombre del archivo comprimido
    char compressedFilename[256];
    snprintf(compressedFilename, sizeof(compressedFilename), "%s.huff", filename);

    FILE *compressedFile = fopen(compressedFilename, "wb");
    if (compressedFile == NULL) {
        printf("No se pudo crear el archivo comprimido %s\n", compressedFilename);
        fclose(file);
        return 0;  // Return 0 to indicate failure
    }

    // Contar la cantidad total de caracteres
    unsigned int totalChars = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        totalChars++;
    }

    // Escribir el header de 3 bytes con la cantidad de caracteres ASCII
    fwrite(&totalChars, sizeof(unsigned int), 1, compressedFile);

    // Volver al inicio del archivo para leer y comprimir
    rewind(file);

    // Inicializar el buffer y contar bits
    unsigned char buffer = 0;
    int bitCount = 0;
    unsigned int compressedSize = 3;  // Contamos el header de 3 bytes

    // Imprimir tabla de códigos Huffman encontrados por carácter
    printf("\nCarácter\tASCII\tCódigo Huffman\n");
    printf("---------------------------------\n");

    while ((c = fgetc(file)) != EOF) {
        char *code = huffmanCodes[(unsigned char)c].code;

        // Imprimir carácter, su código ASCII y el código Huffman
        printf("%c\t\t%d\t%s\n", (char)c, (unsigned char)c, code);

        // Procesar cada bit del código Huffman
        for (int i = 0; code[i] != '\0'; i++) {
            if (code[i] == '1') {
                buffer |= (1 << (7 - bitCount));  // Asignar el bit correspondiente en el buffer
            }
            bitCount++;

            // Si el buffer tiene 8 bits llenos, escribirlo al archivo
            if (bitCount == 8) {
                fwrite(&buffer, sizeof(unsigned char), 1, compressedFile);
                compressedSize++;
                buffer = 0;
                bitCount = 0;
            }
        }
    }

    // Escribir cualquier bit restante en el buffer
    if (bitCount > 0) {
        fwrite(&buffer, sizeof(unsigned char), 1, compressedFile);
        compressedSize++;
    }

    fclose(file);
    fclose(compressedFile);

    // Actualizar información de archivo
    strncpy(fileInfo->filename, filename, sizeof(fileInfo->filename));
    fileInfo->originalSize = totalChars;
    fileInfo->compressedSize = compressedSize;

    printf("Archivo %s comprimido como %s\n", filename, compressedFilename);

    return 1;  // Return 1 to indicate success
}