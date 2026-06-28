#include<stdio.h>

int main(){
    int n,a,b;
    printf("Enter the length of array :");
    scanf("%d",&n);
    int arr[n];


    //input 
    printf("Enter you %d integers for arr:", n);
    for(int i = 0; i < n;i++){
        scanf("%d",&arr[i]);
    }
    // printf("Enter you %d integers for y:", n);
    // for(int i = 0; i < n;i++){
    //         scanf("%d",&y[i]);
    // }
    printf("Enter x :");
    scanf("%d" ,&a);
    printf("Enter y :");
    scanf("%d",&b);
    //swap
    for(int i = 0; i<n ; i++){
        if(arr[i] == a){
            arr[i] = b;
        }
    }

    printf("Swaped Array X\n");
    for(int i = 0; i < n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");

    // printf("Swaped Array Y\n");
    // for(int i = 0; i < n;i++){
    //     printf("%d ",y[i]);
    // }
    printf("\n");

}