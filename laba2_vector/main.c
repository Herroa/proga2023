#include <stdio.h>
#include "IntVector.h"

int main()
{   
    size_t capacity = 15;
    IntVector *array = int_vector_new(capacity);
    // int_vector_free(array);
    
    for(int i = 0;i<capacity;i++){
        array->data[i] = i;
        printf("%d ", array->data[i]);
    } printf("\n");

    printf("%d\n",int_vector_get_item(array,5));
    int_vector_set_item(array, 5, 100);
    printf("%d\n",int_vector_get_item(array,5));
    printf("%zu\n", int_vector_get_capacity(array));
    return 0;
}
