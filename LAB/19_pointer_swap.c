#include<stdio.h>

int main(){
    int n,a,b;
    printf("Enter the length of array :");
    scanf("%d",&n);
    int *arr = malloc(n * sizeof(int));

    printf("Enter you %d integers for arr:", n);
    for(int i = 0; i < n;i++){
        scanf("%d",arr + i);
    }
    printf("Enter x :");
    scanf("%d" ,&a);
    printf("Enter y :");
    scanf("%d",&b);
    for(int i = 0; i<n ; i++){
        if(*(arr + i) == a){
            *(arr + i) = b;
        }
    }

    printf("Swaped Array X\n");
    for(int i = 0; i < n;i++){
        printf("%d ",*(arr + i));
    }
    printf("\n");


}