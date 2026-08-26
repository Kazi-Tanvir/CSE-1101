#include<stdio.h>

int factorial(int n){
    if(n==0) return 1;
    return n*factorial(n-1);
}

int main(){
    int n;
    printf("Enter the number of rows: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            printf("%d ",factorial(i)/(factorial(j)*factorial(i-j)));
        }
        printf("\n");
    }
    return 0;
}