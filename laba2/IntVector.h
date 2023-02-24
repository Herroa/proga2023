#include <stdlib.h>

typedef struct{
    int *data;
    size_t size;
    size_t capacity;
} IntVector;

IntVector *int_vector_new(size_t initial_capacity);