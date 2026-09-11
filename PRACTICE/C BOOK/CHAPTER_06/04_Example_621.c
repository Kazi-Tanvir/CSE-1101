#include<stdio.h>

int main(){
    char *chp , ch;
    int *ip,i;
    float *fp ,f;
    double *dp,d;

    chp = &ch;
    ip = &i;
    fp = &f;
    dp = &d;

    printf("%u %u %u %u\n", chp,ip ,fp ,dp );
    
    chp++;
    ip++;
    fp++;
    dp++;
    
    printf("%u %u %u %u\n", chp,ip ,fp ,dp );

    return 0;

}