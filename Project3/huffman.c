#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "huffman.h"

HuffmanNode* createNode(char character, int freq) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->character = character;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

MinHeap* createMinHeap(int maxSize) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->maxSize = maxSize;
    minHeap->array = (HuffmanNode**)malloc(minHeap->maxSize * sizeof(HuffmanNode*));
    return minHeap;
}

void swapNodes(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->size && 
        minHeap->array[left]->freq < minHeap->array[smallest]->freq) {
        smallest = left;
    }

    if (right < minHeap->size && 
        minHeap->array[right]->freq < minHeap->array[smallest]->freq) {
        smallest = right;
    }

    if (smallest != index) {
        swapNodes(&minHeap->array[smallest], &minHeap->array[index]);
        minHeapify(minHeap, smallest);
    }     
}

void insertMinHeap(MinHeap* minHeap, HuffmanNode* node) {
    minHeap->size++;
    int i = minHeap->size - 1;

    while (i && node->freq < minHeap->array[(i-1)/2]->freq) {
        minHeap->array[i] = minHeap->array[(i-1)/2];
        i = (i -1) / 2;
    }

    minHeap->array[i] = node;
}

HuffmanNode* extractMin(MinHeap* minHeap) { 
    HuffmanNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i) {
        minHeapify(minHeap, i);
    }
}

MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i) {
        minHeap->array[i] = createNode(data[i], freq[i]);
    }

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

HuffmanNode* buildHuffmanTree(char data[], int freq[], int size) {
    printf("HOLA; EMPECAREA  CREAR");
    HuffmanNode *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = createNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    printf("HOLA termine  CREAR");
    return extractMin(minHeap);  // The root node
}

void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
} 

int isSizeOne(MinHeap* minHeap) 
{ 
  
    return (minHeap->size == 1); 
} 

int isLeaf(HuffmanNode* root) 
  
{ 
  
    return !(root->left) && !(root->right); 
} 

void printCodes(HuffmanNode* root, int arr[], int top, char* codes[], char symbols[], int size) {
    if (root->left) { 
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1, codes, symbols, size); 
    }
  
    if (root->right) { 
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1, codes, symbols, size); 
    }
  
    if (isLeaf(root)) {
        // Convertir el array de 0s y 1s en un string y almacenarlo en codes[]
        char code[top + 1];
        for (int i = 0; i < top; i++) {
            code[i] = arr[i] + '0';  // Convertir de entero a char ('0' o '1')
        }
        code[top] = '\0';  // Terminar el string

        // Encontrar el índice del símbolo actual en el arreglo symbols[]
        for (int i = 0; i < size; i++) {
            if (symbols[i] == root->character) {
                codes[i] = strdup(code);  // Almacenar el código
                break;
            }
        }
    }
}

void serializeTree(FILE* file, HuffmanNode* node) {
    if (node == NULL) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        // Leaf node
        fprintf(file, "1:%02X:%d ", (unsigned char)node->character, node->freq);
        if (node->character == 'a') {
            printf("Found 'a' with frequency: %d\n", node->freq);
        }
    } else {
        // Internal node
        fprintf(file, "0:%d ", node->freq);
        serializeTree(file, node->left);
        serializeTree(file, node->right);
    }
}




HuffmanNode* deserializeTree(FILE* file) {
    int flag;
    unsigned int hexVal;
    int frequency;

    // Read the flag indicating the type of node (leaf or internal)
    if (fscanf(file, "%d", &flag) != 1) {
        fprintf(stderr, "Error reading flag\n");
        return NULL;  // End of file or error
    }

    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    if (flag == 1) {
        // Leaf node: read character as hex and frequency
        if (fscanf(file, ":%02X:%d", &hexVal, &frequency) == 2) {
            node->character = (char)hexVal;
            node->freq = frequency;
            node->left = node->right = NULL;
        } else {
            fprintf(stderr, "Error reading hex value or frequency\n");
            free(node);  // Free allocated memory if reading fails
            return NULL;  // Handle unexpected format
        }
    } else {
        // Internal node: read frequency
        if (fscanf(file, ":%d", &frequency) == 1) {
            node->character = '\0';  // Internal nodes do not have characters
            node->freq = frequency;
            node->left = deserializeTree(file);
            node->right = deserializeTree(file);
        } else {
            fprintf(stderr, "Error reading frequency\n");
            free(node);  // Free allocated memory if reading fails
            return NULL;  // Handle unexpected format
        }
    }

    return node;
}


// Helper function to print the tree (pre-order traversal)
void printTreeHelperToFile(HuffmanNode* root, int depth, FILE* file) {
    if (root == NULL) {
        for (int i = 0; i < depth; i++) fprintf(file, "  ");
        fprintf(file, "NULL\n");
        return;
    }

    for (int i = 0; i < depth; i++) fprintf(file, "  ");
    if (root->left == NULL && root->right == NULL) {
        fprintf(file, "Leaf: '%c' (Freq: %d)\n", root->character, root->freq);
    } else {
        fprintf(file, "Internal Node (Freq: %d)\n", root->freq);
    }

    printTreeHelperToFile(root->left, depth + 1, file);
    printTreeHelperToFile(root->right, depth + 1, file);
}

void printTreeToFile(HuffmanNode* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }
    printTreeHelperToFile(root, 0, file);
    fclose(file);
}





void HuffmanCodes(char data[], int freq[], int size, char* codes[], char *headerFile2) {
    HuffmanNode* root = buildHuffmanTree(data, freq, size);

    // Abrir archivo para escribir el árbol serializado
    FILE *treeFile = fopen(headerFile2, "w");
    
    serializeTree(treeFile, root);

    
    fclose(treeFile);

    // Imprimir códigos de Huffman
    int arr[256], top = 0;
    printCodes(root, arr, top, codes, data, size);

    FILE* file = fopen("huffman_tree.h", "r");
    if (!file) {
        fprintf(stderr, "Error opening file\n");
    }

    HuffmanNode* root2 = deserializeTree(file);
    fclose(file);

    printTreeToFile(root2, "tree_structure_deserialized.txt");
    printTreeToFile(root, "tree_structure_before_serialization.txt");


}
