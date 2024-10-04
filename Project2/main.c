#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
        printf("\n");
        return 0;
    }

    // si no ocurre ninguno de los casos anteriores
    // procesar toda la lista de archivos
    int frequencyArray[256] = {0};
    int frequency;
    char buffer[256];
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

    return 0;
}