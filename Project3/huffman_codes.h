#ifndef HUFFMAN_CODES_H
#define HUFFMAN_CODES_H

typedef struct {
    char symbol;
    char *code;
} HuffmanCode;

HuffmanCode huffmanCodes[] = {
    { 'a', "1" },
    { 'b', "0" },
};

#endif // HUFFMAN_CODES_H
