#include<stdio.h>

int main(){
    int *p , q = 0;
    p = &q;
    *p++;
    printf("%d %d %u \n", q,*p,p);
    *p--;
    (*p)++;
    printf("%d %d %u \n", q,*p,p);


    return 0;
}