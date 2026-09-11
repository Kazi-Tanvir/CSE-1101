// wrong pointer type example : throws error 
#include<stdio.h>

int main(){
    int *p;
    double q , temp;

    temp = 124.26;
    p = &temp;
    q = *p;
    
    printf("%f",q);
    return 0;
}