#include <stdio.h>
#include "IntVector.h"

int main()
{   
    size_t capacity = 10;
    IntVector *array1 = int_vector_new(capacity);
    for(int i = 0;i<capacity;i++){
        printf("%d ", array1->data[i]);
    } 
    printf("\n");
    return 0;
}
