#include<stdio.h>
#include<stdlib.h>

int sum(int* arr, int n){
    if(n < 0) return 0;
    return *(arr + n) + sum(arr ,n-1);
}

int main(){
    int n;
    printf("Enter the length of array :");
    scanf("%d",&n);
    int *arr = (int*) malloc(n * sizeof(int));

    printf("Enter you %d integers :", n);
    for(int i = 0; i < n;i++){
        scanf("%d",arr + i);
    }

    if(arr == NULL) return 0;

    printf("The Summ is %d \n" , sum(arr , n -1));   
    free(arr);
}