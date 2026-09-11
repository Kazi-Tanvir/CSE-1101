#include <stdio.h>

int main(void)
{
    int *p, **mp;
    int num = 5;

    p = &num;
    mp = &p;

    printf("%d %d %d\n",*p,**mp,num);
    printf("%u %u %u\n",&p,&mp,&num);

    return 0;
}