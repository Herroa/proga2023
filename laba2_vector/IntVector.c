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

//size
size_t int_vector_get_capacity(const IntVector *v)
{
    return v->capacity;
}