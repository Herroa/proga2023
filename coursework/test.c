#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// char *mur(char *str1,char *str2){
//     char *istr = NULL;

// }

int *create_sample(char *template)
{
    int N = strlen(template), i, j;
    int *sample = malloc(sizeof(int) * N);
    for (i = N - 2; i > -1; i--)
    {
        sample[i] = N - i - 1;
        for (j = N - 2; j > i; j--)
        {
            if (template[i] == template[j])
            {
                sample[i] = sample[j];
                break;
            }
        }
    }
    sample[N - 1] = N;
    for (i = N - 1; i > -1; i--)
    {
        if (template[N - 1] == template[i])
        {
            sample[N - 1] = sample[i];
            break;
        }
    }
    return sample;
}

int main()
{
    char string[12] = "rr romma";
    char template[10] = "romma";
    int *sample = create_sample(template);

    for (int i = 0; i < strlen(template); i++)
    {
        printf("%d", sample[i]);
    }
    printf("\n");

    for (int i = 0; i < strlen(string); i++)
    {
        for(int j=i,k=0;j<strlen(template);j++,k++){
            if(string[j]!=template[j])
            {
                i+=sample[k];
                break;
            }
        }
    }

    free(sample);
    return 0;
}