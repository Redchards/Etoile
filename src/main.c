#include <entropy.h>
#include <binaryTree.h>

#include <hashtable.h>

int main(int argc, char** argv)
{
	/*HuffmanCode* d = malloc(sizeof(HuffmanCode));
	d->codeValue = 24;
	d->codeLength = 2;
	HuffmanCode* de = malloc(sizeof(HuffmanCode));
	de->codeValue = 12;
	de->codeLength = 5;
	
	HashTable* lol = new_hashtable(700);
	set(lol, "e", d);
	set(lol, "de", de);
	//set(lol, "e", d);
	//get(lol, "e");
	printf("%d\n", get(lol, "de")->codeValue);
	printf("%d\n", get(lol, "e")->codeValue);

	for(int i = 0; i < 50; i++)
	{
		d = malloc(sizeof(HuffmanCode));
		d->codeValue = i;
		char* j = &i;
		set(lol, j, d);
	}

		for(int i = 10; i >= 0; i--){ 	char* j = &i;	printf("%d\n", get(lol, j)->codeValue); }		delete_hashtable(lol);*/
	/*char_size_t_pair coucou;
	coucou.value = 5.0;
	coucou.key = 'c';
	
	char_size_t_pair coucou2;
	coucou2.value = 6.0;
	coucou2.key = 'd';
	
	char_size_t_pair coucou3;
	coucou3.value = 3.0;
	coucou3.key = 'e';
	
	char_size_t_pair coucou4;
	coucou4.value = 10.0;
	coucou4.key = 'f';
	
	char_size_t_pair coucou5;
	coucou5.value = 1.0;
	coucou5.key = 't';
	
	char_size_t_pair coucou6;
	coucou6.value = 18.0;
	coucou6.key = 't';
	
	char_size_t_pair coucou7;
	coucou7.value = 3.4;
	coucou7.key = 't';
	
	char_size_t_pair coucou8;
	coucou8.value = 0.2;
	coucou8.key = 'x';
	
	Heap* heap = new_heap(256);
	
	insert(coucou, NULL, NULL, heap);
	insert(coucou6, NULL, NULL, heap);
	insert(coucou2, NULL, NULL, heap);
	insert(coucou3, NULL, NULL, heap);
	insert(coucou4, NULL, NULL, heap);
	insert(coucou5, NULL, NULL, heap);
	insert(coucou6, NULL, NULL, heap);
	insert(coucou7, NULL, NULL, heap);
	insert(coucou8, NULL, NULL, heap);
	insert(coucou8, NULL, NULL, heap);
	insert(coucou8, NULL, NULL, heap);
	insert(coucou8, NULL, NULL, heap);
	insert(coucou8, NULL, NULL, heap);
	insert(coucou7, NULL, NULL, heap);
	insert(coucou7, NULL, NULL, heap);
	insert(coucou7, NULL, NULL, heap);
	insert(coucou3, NULL, NULL, heap);
	insert(coucou3, NULL, NULL, heap);
	insert(coucou3, NULL, NULL, heap);
	insert(coucou3, NULL, NULL, heap);
	insert(coucou3, NULL, NULL, heap);
	insert(coucou3, NULL, NULL, heap);
	insert(coucou4, NULL, NULL, heap);
	insert(coucou5, NULL, NULL, heap);
	insert(coucou6, NULL, NULL, heap);
	insert(coucou7, NULL, NULL, heap);*/
	//sort(heap);

	//print_heap(heap, heap->begin);
	
	if(argc != 1)
	{
		if(argc > 2)
		{
			printf("Too much arguments were given, only the first path will be used\n");
		}
		//char_float_pair** entropy = get_byte_entropy(argv[1]);
		FILE* tmpFile = fopen(argv[1], "rb");
		FILE* ld = fopen("newFile.new", "w");
		//HashTable* code = get_huffman_code(tmpFile);
		encode(tmpFile);
		//clean_file_buffer();
		fclose(tmpFile);
		fclose(ld);
		
		/*HuffmanCode* l = get(code, "r");
		printf("\n%p", l);
		printf("\n");
		for(int i = 0; i < l->codeLength && l != NULL; i++)
		{
			printf("%d", (l->codeValue & ( 1 << i)) >> i);
		}*/
		printf("\n");
		//delete_hashtable(code);
		//delete_heap(heap);
		//sort(heap);
		/*for(int i = 0; i < 256; i++)
		{
			printf("%p and %p and is at adress %p and has value of %d\n",heap->begin[i].left, heap->begin[i].right, &heap->begin[i], heap->begin[i].data.value);
		}
		delete_heap(heap);*/
		/*if(entropy[0] != NULL)
		{
			printf("SUMMARY OF CHARACTERS ENTROPY\n\n");
			for(int i = 0; i < 256; i++)
			{
				printf("%2X  :  %f\n", entropy[i]->key, entropy[i]->value);
			}
		
			free_double_array(entropy);
		}*/
	}
	else
	{
		printf("The program must take at least one file path as argument !!\n");
	}
	return 0;
}
