#ifndef STRUCTPAIRS_H
#define STRUCTPAIRS_H

#define MAKE_PAIR(keyType, valueType) \
typedef struct \
{ \
	keyType key; \
	valueType value; \
} keyType##_##valueType##_##pair;

#define MAKE_PAIR_KEYPTR(keyType, valueType) \
typedef struct \
{ \
	keyType* key; \
	valueType value; \
} keyType##Ptr##_##valueType##_##pair;

#endif // STRUCTPAIRS_H
