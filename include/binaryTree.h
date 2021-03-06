#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <structPairs.h>

MAKE_PAIR(char, long);

typedef struct node
{
	struct node* left;
	struct node* right;
	char_long_pair data;
} TreeNode;

typedef struct
{
	TreeNode* begin;
	TreeNode* end;
	long count;
	size_t maxCapacity;
} Heap;

Heap* new_heap(size_t size);
void delete_heap(Heap* heap);
void organize(Heap* heapPtr, int index);
void organizePtr(Heap* heapPtr, int index);
void organize_insert(Heap* heapPtr, int index);
void organize_insert_rev(Heap* heapPtr, int index);
void max_heapify(Heap* heapPtr, int index);
void insert_no_links(char_long_pair data, TreeNode* right, TreeNode* left, Heap* heapPtr);
void insert(char_long_pair data, TreeNode* right, TreeNode* left, Heap* heapPtr);
void insert_rev(char_long_pair data, TreeNode* right, TreeNode* left, Heap* heapPtr);
void sort(Heap* heapPtr);
void sortPtr(Heap* heapPtr);
void print_heap(Heap* heap, TreeNode* current);
void swapValue(TreeNode* x, TreeNode* y);
void swap(TreeNode* x, TreeNode* y);

#endif // BINARY_TREE_H
