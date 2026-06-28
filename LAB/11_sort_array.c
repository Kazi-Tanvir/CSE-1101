#include<stdio.h>

int main(){
    int n;
    printf("Enter the length of array :");
    scanf("%d",&n);
    int arr[n];

    //input 
    printf("Enter you %d integers :", n);
    for(int i = 0; i < n;i++){
        scanf("%d",&arr[i]);
    }

    for(int i = 0;i<n;i++){
        for(int j = i + 1 ; j < n ;j++){
            if(arr[j]>arr[i]){
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }

    printf("Sorted Array\n");
    for(int i = 0; i < n;i++){
        printf("%d ",arr[i]);
    }
    printf("The Minimum number is : %d\n" ,arr[n-1]);
    printf("The Maximum number is : %d\n" ,arr[0]);
    
    printf("\n");

}