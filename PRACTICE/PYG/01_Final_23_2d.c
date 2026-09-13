#include<stdio.h>

int Divisor(int n){
    if(n == 2) return 1;
    for(int i = 2 ; i < n; i++ ){
        if(n%i==0) return i;
    }
    return 1;
}

int main(void){
    int n = 23;
    int k = 0;
    printf("%d\n",n);
    for(int i = 1;;i++){
        for(int j = 0; j < k ; j++){
            printf(" ");
        }
        int divisor = Divisor(n);
        if(divisor == 1){
            printf("%d %d",n,divisor);
            break;
        }
        else{
            printf("%d %d\n",divisor,n/divisor);
            n = n/divisor;
            k++;
        }
    }
}