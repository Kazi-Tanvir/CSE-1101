#include<stdio.h>

int main(){
    int n,m;
    printf("Enter the length of array arr1:");
    scanf("%d",&n);
    printf("Enter the length of array Y:");
    scanf("%d",&m);
    int arr1[n];
    int arr2[m];
    int arr3[n+m];


    //input 
    printf("Enter you %d integers for x:", n);
    for(int i = 0; i < n;i++){
        scanf("%d",&arr1[i]);
    }
    printf("Enter you %d integers for Y:", m);
    for(int i = 0; i < m;i++){
        scanf("%d",&arr2[i]);
    }

    for (int i = 0; i < n; i++) {
        arr3[i] = arr1[i];
    }

for (int i = 0; i < n+m; i++) {
    arr3[i + n] = arr2[i];
}




    for(int i = 0;i<n+m;i++){
        for(int j = i + 1 ; j < 10 ;j++){
            if(arr3[j]>arr3[i]){
                int temp = arr3[j];
                arr3[j] = arr3[i];
                arr3[i] = temp;
            }
        }
    }

    printf("Sorted array\n");
    for(int i = 0 ; i < m+n ; i++){
        printf("%d ",arr3[i]);
    }
        printf("\n");
}