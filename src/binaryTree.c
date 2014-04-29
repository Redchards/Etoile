#include <binaryTree.h>

Heap* new_heap(size_t size)
{
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	heap->begin = (TreeNode*)calloc(size, sizeof(TreeNode));
	assert(heap->begin != NULL);
	heap->end = heap->begin;
	heap->maxCapacity = size;
	
	return heap;
}

void delete_heap(Heap* heap)
{
	free(heap->begin);
	free(heap);
}

void organize(Heap* heapPtr, int index)
{
	TreeNode* heap = heapPtr->begin;
	int maxIndex = index;
	TreeNode parentValue = heap[index];
	int j;
	
	for(j = (maxIndex<<1)+1; j<(heapPtr->count-1); j<<=1, j++)
	{
		if(heap[j].data.value < heap[j+1].data.value)
		{
			j++;
		}

		if(heap[j].data.value <= parentValue.data.value) break;
		heap[index].data = heap[j].data;
		index = j;
	}
	
	if(j == (heapPtr->count-1) && heap[j].data.value > parentValue.data.value)
	{
		heap[index].data = heap[j].data;
		index = j;
	}
	
	heap[index].data = parentValue.data;
}

void organizePtr(Heap* heapPtr, int index)
{
	TreeNode* heap = heapPtr->begin;
	int maxIndex = index;
	TreeNode parentValue = heap[index];
	int j;
	
	for(j = (maxIndex<<1)+1; j<(heapPtr->count-1); j<<=1, j++)
	{
		if(heap[j].data.value < heap[j+1].data.value)
		{
			j++;
		}

		if(heap[j].data.value <= parentValue.data.value) break;
		heap[index] = heap[j];
		index = j;
	}
	
	if(j == (heapPtr->count-1) && heap[j].data.value >= parentValue.data.value)
	{
		heap[index] = heap[j];
		index = j;
	}
	
	heap[index] = parentValue;
}

void organize_insert(Heap* heapPtr, int index)
{
	TreeNode* heap = heapPtr->begin;
	int maxIndex = index;
	int i;
	while(maxIndex != 0)
	{
		i = (maxIndex-1) / 2;
		
		if(heap[i].data.value >= heap[maxIndex].data.value)
		{
			break;
		}
		swapValue(&heap[maxIndex], &heap[i]);
		maxIndex = i;
	}
}

void organize_insert_rev(Heap* heapPtr, int index)
{
	TreeNode* heap = heapPtr->begin;
	int maxIndex = index;
	int i;
	while(maxIndex != 0)
	{
		i = (maxIndex-1) / 2;
		
		if(heap[i].data.value <= heap[maxIndex].data.value)
		{
			break;
		}
		swap(&heap[maxIndex], &heap[i]);
		maxIndex = i;
	}
}

void max_heapify(Heap* heapPtr, int index)
{
	int maxIndex = index;

	if(heapPtr->begin[index].left != NULL && heapPtr->begin[index].left->data.value > heapPtr->begin[index].data.value)
	{
		maxIndex = 2*index;
	}
	
	if(heapPtr->begin[index].right!= NULL && heapPtr->begin[index].right->data.value > heapPtr->begin[maxIndex].data.value)
	{
		maxIndex = 2*index+1;
	}
	
	if(maxIndex != index)
	{
		swapValue(&heapPtr->begin[index], &heapPtr->begin[maxIndex]);
		max_heapify(heapPtr, maxIndex);
	}
}

void insert(char_long_pair data, TreeNode* right, TreeNode* left, Heap* heapPtr)
{

	TreeNode* newNode = NULL;
	
	newNode = (heapPtr->end)++;
	assert(newNode != NULL);
	
	++(heapPtr->count);
	if(data.value || right == NULL || left == NULL)
	{
		newNode->data = data;
		newNode->left = &heapPtr->begin[heapPtr->count*2-1];
		newNode->right = &heapPtr->begin[heapPtr->count*2];
	}
	else
	{
		newNode->left = left;
		newNode->right = right;
		newNode->data.value = left->data.value + right->data.value;
		heapPtr->begin += 2;
		heapPtr->count -= 2;
	}
	heapPtr->begin[heapPtr->count-1] = *newNode;
	
	organize_insert(heapPtr, heapPtr->count-1);

}

void insert_rev(char_long_pair data, TreeNode* right, TreeNode* left, Heap* heapPtr)
{
	TreeNode* newNode = NULL;
	
	newNode = (heapPtr->end)++;
	assert(newNode != NULL);
	
	++(heapPtr->count);
	if(data.value || right == NULL || left == NULL)
	{
		newNode->data = data;
		newNode->left = &heapPtr->begin[heapPtr->count*2-1];
		newNode->right = &heapPtr->begin[heapPtr->count*2];
	}
	else
	{
		newNode->left = left;
		newNode->right = right;
		newNode->data.value = left->data.value + right->data.value;
		heapPtr->begin += 2;
		heapPtr->count -= 2;
	}
	heapPtr->begin[heapPtr->count-1] = *newNode;
	
	organize_insert_rev(heapPtr, heapPtr->count-1);

}

void insert_no_links(char_long_pair data, TreeNode* right, TreeNode* left, Heap* heapPtr)
{

	TreeNode* newNode = NULL;
	
	newNode = (heapPtr->end)++;
	assert(newNode != NULL);
	if(data.value || right == NULL || left == NULL)
	{
		newNode->data = data;
	}
	++(heapPtr->count);
	heapPtr->begin[heapPtr->count-1] = *newNode;
	organize_insert(heapPtr, heapPtr->count-1);

}

void sort(Heap* heapPtr)
{
	int tmp = heapPtr->count;
	while(heapPtr->count > 0)
	{
		--(heapPtr->count);
		swapValue(&heapPtr->begin[heapPtr->count], &heapPtr->begin[0]);
		organize(heapPtr, 0);

	}
	heapPtr->count = tmp;
}

void sortPtr(Heap* heapPtr)
{
	int tmp = heapPtr->count;
	while(heapPtr->count > 0)
	{
		--(heapPtr->count);
		swapValue(&heapPtr->begin[heapPtr->count], &heapPtr->begin[0]);
		organizePtr(heapPtr, 0);

	}
	heapPtr->count = tmp;
}

void print_heap(Heap* heap, TreeNode* current)
{
	if(current != NULL)
	{
		printf("Key %c, value %d\n", (char)current->data.key, current->data.value);
		print_heap(heap, current->left);
		print_heap(heap, current->right);
	}
}

void swapValue(TreeNode* restrict x, TreeNode* restrict y)
{
	char_long_pair tmp = x->data;
	x->data = y->data;
	y->data = tmp;
}
void swap(TreeNode* restrict x, TreeNode* restrict y)
{
	TreeNode tmp = *x;
	*x = *y;
	*y = tmp;
}
