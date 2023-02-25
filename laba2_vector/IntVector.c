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
    v->size = initial_capacity;
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
    if(index < v->size){
        v->data[index] = item;
    }
}


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
        return 0;
    }
    else{
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity);
        if(!v){
            return -1;
        }
        else{
            v->data[v->size++] = item;
            return 0;
        }
    }
}

void int_vector_pop_back(IntVector *v)
{
    if(v->size != 0)
    {
        v->data[v->size] = 0;
        v->size--;
    }
}
//delete >0?

int int_vector_shrink_to_fit(IntVector *v)
{
    v->capacity = v->size;
    v->data = realloc(v->data,v->size);
    if(!v){
        v->capacity = v->size;
        return -1;
    }
    else{
        return 0;
    }
}
//realloc doesnt save half of data

