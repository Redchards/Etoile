#include <entropy.h>

/* Overhead to reading one byte at time according to stackoverflow question
		http://stackoverflow.com/questions/6093224/reading-a-binary-file-1-byte-at-a-time-c
		Tell OS to read from the file.
		OS searches to find the file location.
		OS tells disk drive to power up.
		OS waits for disk drive to get up to speed.
		OS tells disk drive to position to the correct track and sector.
		-->OS tells disk to read one byte and put into drive buffer.
		OS fetches data from drive buffer.
		Disk spins down to a stop.
		OS returns 1 byte to your program.
		So could be good to use fread and put it into buffer later, this can avoid to read the file
		byte per byte all over for compression. */


// Return array of character entropy for each existing characters.
// It allocate an array of PtrStrFloat* and so must be deallocated,
// free_byte_counter(PairStrFloat**) function can be used
char_float_pair** get_byte_entropy(char* filename)
{
	assert(filename != NULL);

	FILE* tmpFile = fopen(filename, "rb");

	char_long_pair** charCount = get_byte_occurrences(tmpFile);
	char_float_pair** charEntropy = malloc(sizeof(char_float_pair*) * 256);
	
	int filesize = get_filesize(tmpFile);
	
	for(int i = 0; i < 256; i++)
	{
		charEntropy[i] = malloc(sizeof(char_float_pair));
		charEntropy[i]->key = i;
		
		if(charCount[i]->value != 0)
		{
			charEntropy[i]->value = -log((float)charCount[i]->value/filesize)*((float)charCount[i]->value/filesize);
		}
		else
		{
			charEntropy[i]->value = 0;
		}
	}
	
	free_double_array(charCount);
	fclose(tmpFile);
	return charEntropy;
}

// Return array of pair corresponding to number of characters occurrences in file
// This function do allocate an array of type PairStrInt*, and so must be deallocated manually
// later, preferably by the free_byte_counter(PairStrInt**) function
char_long_pair** get_byte_occurrences(FILE* file)
{
	assert(file != NULL);

	char_long_pair** countArray = malloc(sizeof(char_long_pair*) * 256);
	
	for(int i = 0; i < 256; i++)
	{
		countArray[i] = calloc(1, sizeof(char_long_pair));
		countArray[i]->key = (unsigned char)i;
	}
	
	// Absolutely need to be unsigned char, because signed char will get negatives values on binary files for examples, and so
	// countArray[currentKey] will result in and undefined behaviour, and likely to a program fail.
	unsigned char currentKey = 0;

	// Char conversion is needed to avoid unsigned char/signed int conversion, and thus infinite loop ( can never reach EOF value,
	// which is -1, or the maximum value that an int can get in binary representation. An unsigned char can never reach that value !
	while((char)currentKey != EOF)
	{
		currentKey = (unsigned int)fgetc(file);
		
		++(countArray[currentKey]->value);
	}

	return countArray;
}

HashTable* get_huffman_code(FILE* file)
{
	assert(file != NULL);
	resetTimer();
	startTimer();
	char_long_pair mockPair;
	mockPair.value = 0;
	mockPair.key = 0;
	currentFilesize = get_filesize(file);
	leftFilesize = currentFilesize; //h : 00011

	char_long_pair** countArray = malloc(sizeof(char_long_pair*) * 256);
	Heap* sortingHeap = new_heap(512);
	if(fileBuf == NULL)
	{
		fileBuf = (char*)calloc(FILE_BUFFER_SIZE, sizeof(char)); // Sizeof(char) to improve lisibility, otherwise
																   // we could just say 1
	}
	//Heap* huffmanHeap = new_heap(256);
	for(int i = 0; i < 256; i++)
	{
		countArray[i] = calloc(1, sizeof(char_long_pair));
		countArray[i]->key = i;
	}
/*1606431742
	 1603215873
	 11010111*/
	unsigned char currentKey = 0;
	unsigned int minIndex = 0;
	/*while(!feof(file))
	{

		currentKey = (unsigned int)fgetc(file);
		++(countArray[currentKey]->value);
	}
	--(countArray[currentKey]->value);*/
	//rewind(file);
	while(!feof(file))
	{
		if(leftFilesize < FILE_BUFFER_SIZE)
		{
			fread(fileBuf, sizeof(int), leftFilesize, file);
			for(size_t i = 0; i < leftFilesize ; i++)
			{
				++(countArray[(unsigned char)fileBuf[i]]->value);
			}

		}
		else
		{
			// Allocate the buffer here only once
			fread(fileBuf, sizeof(int), FILE_BUFFER_SIZE, file);
			for(size_t i = 0; i < FILE_BUFFER_SIZE; i++)
			{
				++(countArray[(unsigned char)fileBuf[i]]->value);
			}
			leftFilesize -= FILE_BUFFER_SIZE;
		}
	}

	
	for(int i = 0; i < 256; i++)
	{
		insert_no_links(*countArray[i], NULL, NULL, sortingHeap);
	}
	
	
	sortPtr(sortingHeap);
	/*for(int i = 0; i < 256;  i++)
		{
			printf("%p and %p and is at adress %p and has key %d and value of %d\n",sortingHeap->begin[i].left, sortingHeap->begin[i].right, &sortingHeap->begin[i],  sortingHeap->begin[i].data.key, sortingHeap->begin[i].data.value);
		}
		printf("\n\n");*/
	stopTimer();
	double sco = getElapsedTime();
	resetTimer();
	startTimer();

	TreeNode* originalArray = sortingHeap->begin;
	TreeNode* sortedArray = sortingHeap->begin;

	while(sortedArray[minIndex].data.value == 0)
	{
		++minIndex;
		--(sortingHeap->count);
	}
	sortingHeap->begin += minIndex;
	sortedArray = sortingHeap->begin;
	
	size_t tableSize = sortingHeap->count;

	while(1)
	{
		if(sortingHeap->count == 1) break;
		insert_rev(mockPair, &sortedArray[0], &sortedArray[1], sortingHeap);
		sortedArray = sortingHeap->begin;
		//sortPtr(sortingHeap);
		/*for(int j = sortingHeap->count-1; sortedArray[j].data.value < sortedArray[j-1].data.value; j--)
		{
			swap(&sortedArray[j], &sortedArray[j-1]);		
		}*/
		//organize(sortingHeap, sortingHeap->begin);	
	}
			/*for(int i = 0; i < 256;  i++)
		{
			printf("%p and %p and is at adress %p and has key %c and  value of %d\n",sortingHeap->begin[i].left, sortingHeap->begin[i].right, &sortingHeap->begin[i], sortingHeap->begin[i].data.key, sortingHeap->begin[i].data.value);
		}*/
	print_heap(sortingHeap, sortingHeap->begin);
	create_huffman_code(sortingHeap, tableSize);
	sortingHeap->begin = originalArray;
	delete_heap(sortingHeap);
	free_double_array(countArray);
	/*for(int i = 0; i < 512;  i++)
		{
			printf("%p and %p and is at adress %p and has key %d and value of %d\n",sortingHeap->begin[i].left, sortingHeap->begin[i].right, &sortingHeap->begin[i],  sortingHeap->begin[i].data.key, sortingHeap->begin[i].data.value);
		}*/
	stopTimer();
	printf("Time to read file %lf\n", sco);
	printf("Time to proceed %lf\n", getElapsedTime());

	return huffman_code;
}

void create_huffman_code(Heap* heap, size_t tableSize)
{
	huffman_code = new_hashtable(tableSize);
	HuffmanCode newCode;
	newCode.codeValue = 0;
	newCode.codeLength = 0;
	build_code_from_node(heap->begin, newCode);
}

static void build_code_from_node(TreeNode* current, HuffmanCode code)
{
	if(current != NULL && (current->left != NULL || current->right != NULL) )
	{
		++code.codeLength;
		build_code_from_node(current->left, code);
		code.codeValue += 1<<(code.codeLength-1);
		build_code_from_node(current->right, code);
	}
	else if(current != NULL) // Could nest it to avoid doing check second time
	{
		HuffmanCode* tmp = (HuffmanCode*)malloc(sizeof(HuffmanCode));
		tmp->codeLength = code.codeLength;
		tmp->codeValue = code.codeValue;
		char* tmpStr = (char*)malloc(2); // Placeholder, because bug when taking directly current->data.key.
								// In fact, we should set ->data.key as string with proper NULL terminating character
		tmpStr[0] = current->data.key;
		tmpStr[1] = '\0';
	printf("current data key %c\n", current->data.key);
		//set_huffman(huffman_code, current->data.key, tmp);
		set(huffman_code, tmpStr, tmp);
		printf("Key %c code  :  ", current->data.key);
		for(int i = 0; i < code.codeLength; i++)
		{
			printf("%d", (code.codeValue & ( 1 << i)) >> i);
		}
		printf("\n");
		free(tmpStr); // Free the placeholder. Should remove with the placeholder when fix is found
	}
}//11011000

// Return filesize. WARNING : Non-portable. See below for more details
size_t get_filesize(FILE* toProceed)
{
	fseek(toProceed, 0L, SEEK_END); // Non-portable according to doc, but since we will be using only gcc, it's ok
	int filesize = ftell(toProceed);
	
	rewind(toProceed);

	return filesize;
}

void clean_file_buffer()
{
	free(fileBuf);
}

void encode(FILE* file)
{
	HashTable* huffmanCode = get_huffman_code(file);
	char* tmpStr = (char*)malloc(2);
	tmpStr[1] = '\0';
	char tmpByte;
	short offset = 8;
	size_t bufferPtr = 0;
	//memset(fileBuf, 0, FILE_BUFFER_SIZE);
	while(leftFilesize <= currentFilesize)
	{
		char tmp = 0;
		if(leftFilesize < FILE_BUFFER_SIZE)
		{
			for(size_t i = 0; i < leftFilesize; i++)
			{
				//if(leftCodeLength < 0) leftCodeLength = 8;
				tmpStr[0] = fileBuf[i];
				HuffmanCode* c = get(huffmanCode, tmpStr);
				offset -= c->codeLength;
				if(offset < 0)// Normally, code should not be longer than 16, so that might just work
				{
					--i;
					offset += 8;
					fileBuf[bufferPtr++] = tmpByte;
				}
				tmpByte = c->codeValue << offset;
				//printf("so we take %s and we get %d", fileBuf[i], c->codeLength);
				/*for(int j = 0; j < c->codeLength; j++)
				{
					printf("%d", (c->codeValue & (1 << j)) >> j);
				}
				printf("\n");*/
			}
		}
		else
		{
			
			for(size_t i = 0; i < FILE_BUFFER_SIZE; i++)
			{
			
			}
		}
		leftFilesize += FILE_BUFFER_SIZE;
	}
	free(tmpStr);
	delete_hashtable(huffmanCode);
	clean_file_buffer();
}
