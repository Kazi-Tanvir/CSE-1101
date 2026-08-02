#include<stdio.h>

int isPrime(int N,int n){
    if(n <= 1) return 0;
    if(N == 2) return 1;
    if(n*n > N) return 1;
    if(N%n == 0) return 0;
    return isPrime(N,n+1);
} 

int main(){
    int n;
    printf("Enter the upper limit : ");
    scanf("%d" , &n);
    for(int i = 2; i < n; i++){
        if(isPrime(i,2))printf("%d ",i);
    }
    printf("\n");
}