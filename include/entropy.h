#ifndef ENTROPY_H
#define ENTROPY_H

#define FILE_BUFFER_SIZE 50000000

#include <assert.h>
#include <binaryTree.h>
#include <hashtable.h>
#include <huffmanStruct.h>
#include <math.h>
#include <memoryFunctions.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <structPairs.h>
#include <linuxtimer.h>

MAKE_PAIR(char, float);
//MAKE_PAIR(char, int);
//CREATE_LIST_TYPE(char_float_pair);

HashTable* huffman_code;
static char* fileBuf = NULL;
static size_t currentFilesize;
static size_t leftFilesize;

char_float_pair** get_byte_entropy(char* filename);
char_long_pair** get_byte_occurrences(FILE* file);
HashTable* get_huffman_code(FILE* file);
void create_huffman_code(Heap* heap, size_t tableSize);
static void build_code_from_node(TreeNode* current, HuffmanCode code);
size_t get_filesize(FILE* toProceed);
void clean_file_buffer();
void encode(FILE* file);

#endif // ENTROPY_H
