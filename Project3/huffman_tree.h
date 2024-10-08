#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

typedef struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode *left, *right;
} HuffmanNode;

HuffmanNode* buildHuffmanTree() {
    // Construct the tree here using the serialized data
    return NULL; // Replace with actual tree construction logic
}

HuffmanNode* huffmanTree = NULL;
void initHuffmanTree() {
    huffmanTree = malloc(sizeof(HuffmanNode)); // Allocate memory for root
    // Add code to initialize tree nodes here
    // Serialized data: 0 1:01 0 1:02 0 1:03 0 1:04 0 1:05 0 1:06 0 1:07 0 1:08 0 1:09 0 1:0A 0 1:0B 0 1:0C 0 1:0D 0 1:0E 0 1:0F 0 1:10 0 1:11 0 1:12 0 1:13 0 1:14 0 1:15 0 1:16 0 1:17 0 1:18 0 1:19 0 1:1A 0 1:1B 0 1:1C 0 1:1D 0 1:1E 0 1:1F 0 1:20 0 1:21 0 1:22 0 1:23 0 1:24 0 1:25 0 1:26 0 1:27 0 1:28 0 1:29 0 1:2A 0 1:2B 0 1:2C 0 1:2D 0 1:2E 0 1:2F 0 1:30 0 1:31 0 1:32 0 1:33 0 1:34 0 1:35 0 1:36 0 1:37 0 1:38 0 1:39 0 1:3A 0 1:3B 0 1:3C 0 1:3D 0 1:3E 0 1:3F 0 1:40 0 1:41 0 1:42 0 1:43 0 1:44 0 1:45 0 1:46 0 1:47 0 1:48 0 1:49 0 1:4A 0 1:4B 0 1:4C 0 1:4D 0 1:4E 0 1:4F 0 1:50 0 1:51 0 1:52 0 1:53 0 1:54 0 1:55 0 1:56 0 1:57 0 1:58 0 1:59 0 1:5A 0 1:5B 0 1:5C 0 1:5D 0 1:5E 0 1:5F 0 1:60 0 1:61 0 1:62 0 1:63 0 1:64 0 1:65 0 1:66 0 1:67 0 1:68 0 1:69 0 1:6A 0 1:6B 0 1:6C 0 1:6D 0 1:6E 0 1:6F 0 1:70 0 1:71 0 1:72 0 1:73 0 1:74 0 1:75 0 1:76 0 1:77 0 1:78 0 1:79 0 1:7A 0 1:7B 0 1:7C 0 1:7D 0 1:7E 0 1:7F 0 1:80 0 1:81 0 1:82 0 1:83 0 1:84 0 1:85 0 1:86 0 1:87 0 1:88 0 1:89 0 1:8A 0 1:8B 0 1:8C 0 1:8D 0 1:8E 0 1:8F 0 1:90 0 1:91 0 1:92 0 1:93 0 1:94 0 1:95 0 1:96 0 1:97 0 1:98 0 1:99 0 1:9A 0 1:9B 0 1:9C 0 1:9D 0 1:9E 0 1:9F 0 1:A0 0 1:A1 0 1:A2 0 1:A3 0 1:A4 0 1:A5 0 1:A6 0 1:A7 0 1:A8 0 1:A9 0 1:AA 0 1:AB 0 1:AC 0 1:AD 0 1:AE 0 1:AF 0 1:B0 0 1:B1 0 1:B2 0 1:B3 0 1:B4 0 1:B5 0 1:B6 0 1:B7 0 1:B8 0 1:B9 0 1:BA 0 1:BB 0 1:BC 0 1:BD 0 1:BE 0 1:BF 0 1:C0 0 1:C1 0 1:C2 0 1:C3 0 1:C4 0 1:C5 0 1:C6 0 1:C7 0 1:C8 0 1:C9 0 1:CA 0 1:CB 0 1:CC 0 1:CD 0 1:CE 0 1:CF 0 1:D0 0 1:D1 0 1:D2 0 1:D3 0 1:D4 0 1:D5 0 1:D6 0 1:D7 0 1:D8 0 1:D9 0 1:DA 0 1:DB 0 1:DC 0 1:DD 0 1:DE 0 1:DF 0 1:E0 0 1:E1 0 1:E2 0 1:E3 0 1:E4 0 1:E5 0 1:E6 0 1:E7 0 1:E8 0 1:E9 0 1:EA 0 1:EB 0 1:EC 0 1:ED 0 1:EE 0 1:EF 0 1:F0 0 1:F1 0 1:F2 0 1:F3 0 1:F4 0 1:F5 0 1:F6 0 1:F7 0 1:F8 0 1:F9 0 1:FA 0 1:FB 0 1:FC 0 1:FD 0 1:FE 0 1:00 1:FF 
}
#endif // HUFFMAN_TREE_H
