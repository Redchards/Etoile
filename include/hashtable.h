#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <assert.h>
#include <huffmanStruct.h>
#include <limits.h>
#include <memoryFunctions.h>
#include <stdlib.h>

// Simple implementation inspired by
// https://gist.github.com/tonious/1377667

typedef struct entry
{
	char* key;
	HuffmanCode* value;
	struct entry* next;
} Entry;

typedef struct hashTable
{
	size_t size;
	size_t count;
	size_t (*hash_string)(struct hashTable*, char*);
	Entry** table;
	
} HashTable;

HashTable* new_hashtable(size_t size);
HashTable* new_hashtable_spec(size_t size, size_t (*hash_string)(HashTable*, char*));
void delete_hashtable(HashTable* hashtable);
void set(HashTable* hashtable, char* key, HuffmanCode* value);
void set_huffman(HashTable* hashtable, char key, HuffmanCode* value);
HuffmanCode* get(HashTable* hashtable, char* key);
HuffmanCode* get_huffman(HashTable* hashtable, char key);
Entry* new_entry(char* key, HuffmanCode* value);
void delete_entry(HashTable* hashtable, char* key);


// Hash functions
//Default hash function
size_t simple_hash(HashTable* hashtable, char* key);
//Hash function from Dan Bernstein
size_t djb2_hash(HashTable* hashtable, char* key);
//Simple 5 bits rotation hash
size_t rot5_hash(HashTable* hashtable, char* key);

#endif // HASHTABLE_H
