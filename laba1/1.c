#include <stdio.h>
#include <stdlib.h>
void init(int** arr, int n)
//dobavlyaem ukazatel na arr
{
    *arr = malloc(n * sizeof(int));
    //razymenovyvaem
    int i;
    for (i = 0; i < n; ++i)
    {
        (*arr)[i] = i;
    //razymenovyvaem
    }
}
int main()
{
    int* arr = NULL;
    int n = 10;

    init(&arr, n);
    //peredaem adress arr
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}
