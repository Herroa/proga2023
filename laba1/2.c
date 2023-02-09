#include <stdio.h>

typedef struct
{
    int num;
    char str[100];
//stavim stroku v konec, i luchshe vydelit bolshe pamiati
} NumberRepr;

void format(NumberRepr* number)
{
    sprintf(number->str, "%3d", number->num);
}

int main()
{
    NumberRepr number = { .num = 1025 };
    format(&number);
    printf("str: %s\n", number.str);
    printf("num: %d\n", number.num);
    return 0;
}