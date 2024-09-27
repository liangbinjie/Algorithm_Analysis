#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

HuffmanNode* createNode(char character, int freq) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->character = character;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

MinHeap* createMinHeap(int maxSize) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->maxSize = maxSize;
    minHeap->array = (HuffmanNode**)malloc(minHeap->capacity * sizeof(HuffmanNode*));
    return minHeap;
}

void swapNodes(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify() {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->size && 
        minHeap->[left]->freq < minHeap->array[smallest]->freq) {
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

