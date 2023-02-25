#include <stdio.h>
#include "IntVector.h"

void print(IntVector *array)
{
    for(int i = 0;i < array->capacity;i++){
        printf("%d ", array->data[i]);
    } printf("\n");
    for(int i = 0;i < array->size;i++){
        printf("%d ", array->data[i]);
    } printf("\n");
    printf("=============================\n");
}

int main()
{   
    size_t capacity = 15;
    IntVector *array = int_vector_new(capacity);
    for(int i = 0;i < array->size;i++){
        array->data[i] = i;
    } printf("\n");
    // int_vector_free(array);
    print(array);
    int_vector_push_back(array, 10);
    print(array);
    // printf("%d\n",int_vector_get_item(array,5));
    // int_vector_set_item(array, 5, 100);
    // printf("%d\n",int_vector_get_item(array,5));
    // printf("%zu\n", int_vector_get_capacity(array));
    return 0;
}
