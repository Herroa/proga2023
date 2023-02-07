#include <stdio.h>

typedef struct
{
    int num;
    char str[4];

} NumberRepr;

void format(NumberRepr* number)
{
    sprintf(number->str, "%3d", number->num);
}
// after fun in str "102" perepolnenie mb ochen stranno plus pochemuto num soderzhit 1024
// glavanaya problema chto .num stanovitsya 1024 pochemuto
int main()
{
    NumberRepr number = { .num = 1025 };
    format(&number);
    printf("str: %s\n", number.str);
    printf("num: %d\n", number.num);
    return 0;
}
//pomenial mestami char i int i zarabotalo
//aaaa zhest, issa vyravnivania u inta kushaetsya bait poetomu on maximum 1024
