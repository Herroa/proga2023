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
    return v;
}
