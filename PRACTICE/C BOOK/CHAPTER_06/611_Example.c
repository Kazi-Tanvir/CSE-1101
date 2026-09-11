#include<stdio.h>

int main(){
    int *p , q;
    p = &q;
    *p = 1000;
    printf("%d %d %p \n", q,*p,p);
    return 0;
}