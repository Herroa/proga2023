#include "IntVector.h"

IntVector *int_vector_new(size_t initial_capacity)
{  
    IntVector *v = NULL;
    v = malloc(sizeof(*v));
    if(!v){
        return NULL;
    }

    v->data = malloc(initial_capacity * sizeof(int));
    if(!v->data)
    {
        free(v);
        return NULL;
    }
    v->capacity = initial_capacity;
    v->size = initial_capacity/2;
    return v;
}

void int_vector_free(IntVector *v)
{
    free(v->data);
    free(v);
}

int int_vector_get_item(const IntVector *v, size_t index)
{
    return v->data[index];
} 

void int_vector_set_item(IntVector *v, size_t index, int item)
{
    v->data[index] = item;
}
//undefined

size_t int_vector_get_size(const IntVector *v)
{
    return v->size;
}

size_t int_vector_get_capacity(const IntVector *v)
{
    return v->capacity;
}

int int_vector_push_back(IntVector *v, int item)
{
    if(v->size < v->capacity){
        v->data[v->size++] = item;
    }
    else{
        v->capacity += 1;
        v = realloc(v, v->capacity);
        v->data[v->size++] = item;
    }
}
// +8
