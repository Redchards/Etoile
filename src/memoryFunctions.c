#include <memoryFunctions.h>

char* duplicate_string(const char* toCopy)
{
	char* newString = (char*)calloc(strlen(toCopy) + 1, sizeof(char));
	if(newString == NULL)
	{
		return NULL;
	}
	strcpy(newString, toCopy);
	return newString;
}

char* char_to_str(const char c)
{
	char* newStr = calloc(2, 1);
	//newStr = (char){c, '\0'};
	newStr[0] = c;
	newStr[1] = '\0';
	return newStr;
}
