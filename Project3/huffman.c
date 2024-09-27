#include <stdio.h>
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

void printCodes(HuffmanNode* root, int arr[], 
                int top) 
  
{ 
  
    if (root->left) { 
  
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1); 
    } 
  
    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    } 
  
    if (isLeaf(root)) { 
  
        printf("%c: ", root->character); 
        printArr(arr, top); 
    } 
} 

void HuffmanCodes(char data[], int freq[], int size) 
  
{ 
    HuffmanNode* root 
        = buildHuffmanTree(data, freq, size); 
  

    int arr[100], top = 0; 
  
    printCodes(root, arr, top); 
} 