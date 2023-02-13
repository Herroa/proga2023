#include <stdio.h>

#define SQR(x) (float)(x) * (x)

int main()
{
    int y = 1;
    double z = 1.0 / SQR(y + 1);
    //dobavlyaem (), y + 1 => (y + 1)
    printf("z = %lf\n", z);
    return 0;
}
