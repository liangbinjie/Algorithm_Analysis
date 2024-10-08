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
void serializeTree(HuffmanNode* root, FILE* file) {
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        // Nodo hoja: Imprimir el valor en hexadecimal para evitar problemas con caracteres no imprimibles
        fprintf(file, "1:%02X ", (unsigned char)root->character);
    } else {
        // Nodo interno
        fprintf(file, "0 ");
    }

    serializeTree(root->left, file);
    serializeTree(root->right, file);
}



void deserializeTreeHelper(FILE* file, HuffmanNode** node) {
    int flag;
    char character;

    // Read the flag (0 or 1) to determine if this is a leaf node
    if (fscanf(file, "%d", &flag) != 1) {
        return;  // End of file or error
    }

    *node = (HuffmanNode*)malloc(sizeof(HuffmanNode));

    if (flag == 1) {
        // Leaf node: read the character
        if (fscanf(file, " '%c',", &character) == 1) {
            (*node)->character = character;
            (*node)->left = (*node)->right = NULL;
        }
    } else {
        // Internal node: recursively deserialize children
        (*node)->character = '\0';  // Internal nodes don't hold characters
        deserializeTreeHelper(file, &(*node)->left);
        deserializeTreeHelper(file, &(*node)->right);
    }
}

HuffmanNode* deserializeTree(FILE* file) {
    HuffmanNode* root = NULL;
    deserializeTreeHelper(file, &root);
    return root;
}


// Helper function to print the tree (pre-order traversal)
void printTree(HuffmanNode* root) {
    if (root == NULL) {
        printf("sd"); //wtf
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        printf("Leaf: '%c'\n", root->character);
    } else {
        printf("Internal Node\n");
    }

    printTree(root->left);
    printTree(root->right);
}


void HuffmanCodes(char data[], int freq[], int size, char* codes[], char *headerFile2) {
    HuffmanNode* root = buildHuffmanTree(data, freq, size);

    FILE *treeFile;
    treeFile = fopen(headerFile2, "w");

    fprintf(treeFile, "#ifndef HUFFMAN_TREE_H\n");
    fprintf(treeFile, "#define HUFFMAN_TREE_H\n\n");

    // Here you define the HuffmanNode structure or any tree-related structures
    fprintf(treeFile, "typedef struct HuffmanNode {\n");
    fprintf(treeFile, "    char character;\n");
    fprintf(treeFile, "    int frequency;\n");
    fprintf(treeFile, "    struct HuffmanNode *left, *right;\n");
    fprintf(treeFile, "} HuffmanNode;\n\n");

    // Serialize the tree to the file
    fprintf(treeFile, "HuffmanNode* buildHuffmanTree() {\n");
    fprintf(treeFile, "    // Construct the tree here using the serialized data\n");
    fprintf(treeFile, "    return NULL; // Replace with actual tree construction logic\n");
    fprintf(treeFile, "}\n\n");

    // Write the serialized tree
    fprintf(treeFile, "HuffmanNode* huffmanTree = NULL;\n");
    fprintf(treeFile, "void initHuffmanTree() {\n");
    fprintf(treeFile, "    huffmanTree = malloc(sizeof(HuffmanNode)); // Allocate memory for root\n");
    fprintf(treeFile, "    // Add code to initialize tree nodes here\n");
    fprintf(treeFile, "    // Serialized data: ");
    serializeTree(root, treeFile); // Serialize and write to file
    fprintf(treeFile, "\n}\n");

    fprintf(treeFile, "#endif // HUFFMAN_TREE_H\n");

    fclose(treeFile);
    int arr[256], top = 0;
    printCodes(root, arr, top, codes, data, size);  // Pasar codes[] para almacenar los códigos

    FILE* file = fopen("huffman_tree.h", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
    }

    HuffmanNode* root2 = deserializeTree(file);
    fclose(file);

    printf("Deserialized Huffman Tree:\n");
    printTree(root2);

}
