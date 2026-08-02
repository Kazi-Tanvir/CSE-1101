#include<stdio.h>

int fibonacci(int *a, int size){
    if(size == 0) return 0;
    if(size == 1) return a[0];
    return fibonacci(a,size-1) + fibonacci(a,size-2);
}

int main(){
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    printf("%d\n", fibonacci(a,n));
}

