#include "IntVector.h"

IntVector *int_vector_new(size_t initial_capacity)
{  
    IntVector *v = NULL;
    v = malloc(sizeof(*v));
    if(v == NULL){
        return NULL;
    }

    v->data = malloc(initial_capacity * sizeof(int));
    if(v->data == NULL)
    {
        free(v);
        return NULL;
    }
    v->capacity = initial_capacity;
    v->size = initial_capacity/2;
    return v;
}

IntVector *int_vector_copy(const IntVector *v)
{
    IntVector *v2 = NULL;
    v2 = malloc(sizeof(*v));
    if(v2 == NULL){
        return NULL;
    }

    v2->data = malloc(v->capacity * sizeof(int));
    if(v2->data == NULL)
    {
        free(v2);
        return NULL;
    }
    
    for(int i = 0;i<v->capacity;i++){
        v2->data[i] = v->data[i];
    }
    v2->capacity = v->capacity;
    v2->size = v->size;
    return v2;
}

void int_vector_free(IntVector *v)
{
    free(v->data);
    // free(v);
}

int int_vector_get_item(const IntVector *v, size_t index)
{
    if(index < v->size){
        return v->data[index];
    }
    else{
        return -1;
    }
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
        if(v->data == NULL){
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
    if(v->size < v->capacity){
        v->data = realloc(v->data,v->size);
        if(v->data == NULL){
            return -1;
        }
        else{
            v->capacity = v->size;
            return 0;
        }
    }
    else{
        return -1;
    }
}   

//realloc doesnt save half of data

int int_vector_resize(IntVector *v, size_t new_size)
{
    if((new_size > v->size) && (new_size < v->capacity)){
        v->data = calloc(new_size, sizeof(int));
        if(v->data == NULL){
            return -1;
        }
        else{
            v->size = new_size;
            return 0;
        }
    }
    else{
        int_vector_shrink_to_fit(v);
        return -1;
    }
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{   
    if(new_capacity > v->capacity){
        v->data = realloc(v->data, new_capacity);
        if(v->data == NULL){
            return -1;
        }
        else{
            v->capacity = new_capacity;
            return 0;
        }
    }
    else{
        return -1;
    }
}
