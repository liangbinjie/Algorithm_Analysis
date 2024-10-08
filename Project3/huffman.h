#ifndef HUFFMAN_H
#define HUFFMAN_H

typedef struct HuffmanNode {
    char character;
    int freq;
    struct HuffmanNode *left;
    struct HuffmanNode *right
} HuffmanNode;

typedef struct MinHeap {
    int size;
    int maxSize;
    HuffmanNode **array;
} MinHeap;

MinHeap* createMinHeap(int maxSize);
void insertMinHeap(MinHeap* minHeap, HuffmanNode* node);
HuffmanNode* extractMin(MinHeap* minHeap);
void buildMinHeap(MinHeap* minHeap);
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);
HuffmanNode* createNode(char caracter, int freq);
HuffmanNode* buildHuffmanTree(char data[], int freq[], int size);
int isSizeOne(MinHeap* minHeap);
int isLeaf(HuffmanNode* root); 
void printCodes(HuffmanNode* root, int arr[], int top, char* codes[], char symbols[], int size);
void serializeTree(HuffmanNode* root, FILE* file);
void deserializeTreeHelper(FILE* file, HuffmanNode** node);
HuffmanNode* deserializeTree(FILE* file);
void printTree(HuffmanNode* root);
void HuffmanCodes(char data[], int freq[], int size, char* codes[], char *headerFile2);

#endif