#include <hashtable.h>

HashTable* new_hashtable(size_t size)
{
	return new_hashtable_spec(size, &simple_hash);
}

HashTable* new_hashtable_spec(size_t size, size_t (*hash_string)(HashTable*, char*))
{
	HashTable* newTable = NULL;
	
	newTable = (HashTable*)malloc(sizeof(HashTable));
	newTable->count = 0;
	*newTable = (HashTable){0};
	assert(newTable != NULL);
	assert(size >= 1);
	newTable->size = size;
	
	newTable->table = (Entry**)calloc(size, sizeof(Entry*));
	*newTable->table= (Entry*){0};
	assert(newTable->table != NULL);
	
	newTable->hash_string = hash_string;
	
	return newTable;
}

void delete_hashtable(HashTable* hashtable)
{
	Entry* current = NULL;
	Entry* tmp = NULL;
	for(size_t i = 0; i < hashtable->size; i++)
	{
		current = hashtable->table[i];
		if(current != NULL)
		{
			do
			{
				tmp = current->next;
				free(current->key);
				free(current->value);
				free(current);
				current = tmp;
			} while(current != NULL);
		}
	}
	free(hashtable->table);
	free(hashtable);
}

void set(HashTable* hashtable, char* key, HuffmanCode* value)
{
	size_t hashValue = hashtable->hash_string(hashtable, key);
	Entry* tmpNext = hashtable->table[hashValue];
	Entry* tmpLast = tmpNext; // Because otherwise there's rare case when we dereference it as NULL pointer...
							  // And everybody know what dereferencing a NULL pointer mean ... :/
	
	while(tmpNext != NULL && tmpNext->key != NULL && strcmp(key, tmpNext->key) > 0)
	{
		tmpLast = tmpNext;
		tmpNext = tmpNext->next;
	}
	
	if(tmpNext != NULL && tmpNext->key != NULL && strcmp(key, tmpNext->key) == 0)
	{
		free(tmpNext->value);
		tmpNext->value = value;
	}
	else
	{
		++(hashtable->count);
		Entry* newEntry = new_entry(key, value);
		if(tmpNext == hashtable->table[hashValue])
		{
			newEntry->next = tmpNext;
			hashtable->table[hashValue] = newEntry;
		}
		else if(tmpNext == NULL)
		{
			tmpLast->next = newEntry;
		}
		else
		{
			newEntry->next = tmpNext;
			tmpLast->next = newEntry;
		}
	}
}

void set_huffman(HashTable* hashtable, char key, HuffmanCode* value)
{
	char* str = char_to_str(key);
	set_huffman(hashtable, str, value);
	free(str);
}

HuffmanCode* get(HashTable* hashtable, char* key)
{
	size_t hashValue = hashtable->hash_string(hashtable, key);
	
	Entry* currentEntry = hashtable->table[hashValue];
	while(currentEntry != NULL && currentEntry->key != NULL && strcmp(key, currentEntry->key) > 0)
	{
		currentEntry = currentEntry->next;
	}
	
	if(currentEntry == NULL || currentEntry->key == NULL || strcmp(key, currentEntry->key) != 0)
	{
		return NULL;
	}
	return currentEntry->value;
}

HuffmanCode* get_huffman(HashTable* hashtable, char key)
{
	char* str = char_to_str(key);
	HuffmanCode* retVal = get(hashtable, str);
	free(str);
	return retVal;
}

Entry* new_entry(char* key, HuffmanCode* value)
{
	Entry* newEntry = NULL;
	
	newEntry = (Entry*)malloc(sizeof(Entry));
	assert(newEntry != NULL);
	
	newEntry->key = duplicate_string(key);
	assert(newEntry->key != NULL);
	
	newEntry->value = value;
	
	newEntry->next = NULL;
	
	return newEntry;
}

void delete_entry(HashTable* hashtable, char* key)
{
	HuffmanCode* toDelete = get(hashtable, key);
	if(toDelete != NULL)
	{
		free(toDelete);
	}
}


size_t simple_hash(HashTable* hashtable, char* key)
{
	size_t hashValue = 0; // Be careful to initalize it
	for(size_t i = 0; i < strlen(key) && hashValue < ULONG_MAX; i++)
	{
		hashValue <<= 8;
		hashValue += key[i];
	}
	//printf("lol %ld", hashValue % hashtable->size);
	return (hashValue % hashtable->size);
}

size_t djb2_hash(HashTable* hashtable, char* key)
{
	size_t hashValue = 5381; // Magic number
	int c;
	
	while((c = *key++))
	{
		hashValue = ((hashValue << 5) + hashValue) + c;
	}
	
	return hashValue % hashtable->size;
}

size_t rot5_hash(HashTable* hashtable, char* key)
{
	size_t hashValue = 0x55555555;
	
	while(*key)
	{
		hashValue ^= *key++;
		hashValue = ((hashValue << 5) | (hashValue >> 3)); // Circular shift. More details here : 
														   // http://en.wikipedia.org/wiki/Circular_shift
	}
	
	return hashValue % hashtable->size;
}
