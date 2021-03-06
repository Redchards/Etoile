#ifndef MEMORY_FUNCTIONS_H
#define MEMORY_FUNCTIONS_H

#include <stdlib.h>
#include <string.h>

#define CHAR_STR_SIZE 2

// Simple macro to deallocate dynamicaly allocated double array.
// Make use of preprocessor only to avoid rewriting function multiple time for different arguments
// type since the body will be the same. I can't figure out an other way to do this in C
#define free_double_array(X) \
		for(int i = 0; i < 256; i++) /* Should change 256 to pass it in parameter */ \
		{ \
			free(X[i]); \
		} \
		free(X); // End
		
char* duplicate_string(const char* toCopy);
char* char_to_str(const char c);

#endif // MEMORY_FUNCTIONS_H
