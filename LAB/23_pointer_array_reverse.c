#include<stdio.h>

int reverse(int *arr,int start,int end){
    if(start >= end) return 0;
    int temp = *(arr+end);
    *(arr+end) = *(arr+start);
    *(arr+start) = temp ;
    return reverse(arr , start + 1 , end - 1);
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
    reverse(arr ,n - 1 , 0);
    for (int i = 0; i< n ; i++){
        printf("%d",*(arr+i));
    }
    printf("\n");
    free(arr);
}