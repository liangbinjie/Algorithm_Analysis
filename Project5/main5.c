#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "huffman_tree.h" // Include the Huffman tree generated in the previous project

typedef struct {
    char filename[256];
    unsigned int originalSize;
    unsigned int compressedSize;
} FileInfo;

int decompressFile(const char *filename, FileInfo *fileInfo); // Now returns int to indicate success
void handleFileRenaming(const char *outputFilename);
HuffmanNode* createNode(char character, int frequency) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// Entry point for decompression program
int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("No se ingresó un archivo para ejecutar el programa\n");
        return 0;
    }

    // Store information for processed files
    FileInfo fileInfos[argc - 1];
    int processedFileCount = 0;

    // Process each file
    for (int i = 1; i < argc; i++) {
        const char *filename = argv[i];
        // Check if file has a ".huff" extension
        if (strstr(filename, ".huff") == NULL) {
            printf("El archivo %s no tiene la extensión .huff y será ignorado.\n", filename);
            continue;
        }
        
        if (decompressFile(filename, &fileInfos[processedFileCount])) {
            processedFileCount++;  // Increment count only for successfully processed files
        }
    }

    // If no files were processed, print a message
    if (processedFileCount == 0) {
        printf("No se pudo procesar ningún archivo.\n");
        return 0;
    }

    return 0;
}

// Decompress a single file, returns 1 if successful, 0 otherwise
int decompressFile(const char *filename, FileInfo *fileInfo) {
    FILE *compressedFile = fopen(filename, "rb");
    if (compressedFile == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        return 0;
    }

    // Read the original size from the header
    unsigned int originalSize;
    fread(&originalSize, sizeof(unsigned int), 1, compressedFile);

    // Create output filename by removing the ".huff" extension
    char outputFilename[256];
    strncpy(outputFilename, filename, strlen(filename) - 5);
    outputFilename[strlen(filename) - 5] = '\0';

    // Handle renaming if the output file already exists
    handleFileRenaming(outputFilename);

    FILE *outputFile = fopen(outputFilename, "wb");
    if (outputFile == NULL) {
        printf("No se pudo crear el archivo de salida %s\n", outputFilename);
        fclose(compressedFile);
        return 0;
    }

    // Initialize the Huffman tree root node
    HuffmanNode* root = createHuffmanTree();
    HuffmanNode* currentNode = root;

    // Read compressed data and decode
    unsigned char buffer;
    unsigned int decompressedSize = 0;

    while (fread(&buffer, sizeof(unsigned char), 1, compressedFile) && decompressedSize < originalSize) {
        for (int bit = 7; bit >= 0; bit--) {
            // Check the current bit in the buffer
            int isBitSet = (buffer & (1 << bit)) != 0;

            // Navigate the Huffman tree according to the bit
            currentNode = isBitSet ? currentNode->right : currentNode->left;

            // If a leaf node is reached, write the character
            if (currentNode->left == NULL && currentNode->right == NULL) {
                fputc(currentNode->character, outputFile);
                decompressedSize++;
                currentNode = root; // Reset to root for next character

                // Stop if we've written all expected characters
                if (decompressedSize >= originalSize) break;
            }
        }
    }

    fclose(compressedFile);
    fclose(outputFile);

    // Update file information
    strncpy(fileInfo->filename, filename, sizeof(fileInfo->filename));
    fileInfo->originalSize = originalSize;
    struct stat st;
    stat(filename, &st);
    fileInfo->compressedSize = st.st_size;

    printf("Archivo %s descomprimido como %s\n", filename, outputFilename);

    // Check if both the original and backup files exist before running `diff`
    struct stat outputStat, backupStat;
    char backupFilename[512];
    snprintf(backupFilename, sizeof(backupFilename), "%s.prev", outputFilename);

    if (stat(outputFilename, &outputStat) == 0 && stat(backupFilename, &backupStat) == 0) {
        // Run `diff` command to compare original with preexisting if applicable
        char diffCommand[512];
        snprintf(diffCommand, sizeof(diffCommand), "diff -u %.248s %.248s", outputFilename, backupFilename);
        system(diffCommand);
    } else {
        printf("No se pudo ejecutar `diff` ya que uno de los archivos no existe.\n");
    }

    return 1;
}

// Handle renaming of output file if it already exists
void handleFileRenaming(const char *outputFilename) {
    struct stat st;
    if (stat(outputFilename, &st) == 0) {
        // If previous version exists, rename it
        char backupFilename[512];
        snprintf(backupFilename, sizeof(backupFilename), "%s.prev", outputFilename);

        // If .prev already exists, remove it
        if (stat(backupFilename, &st) == 0) {
            remove(backupFilename);
        }
        // Rename existing file to .prev
        rename(outputFilename, backupFilename);
        printf("Archivo existente renombrado a %s\n", backupFilename);
    }
}
