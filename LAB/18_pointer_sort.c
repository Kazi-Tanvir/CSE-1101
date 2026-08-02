#include<stdio.h>
#include <stdlib.h>

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

    for(int i = 0;i<n;i++){
        for(int j = i + 1 ; j < n ;j++){
            if(*(arr+ j)>*(arr+i)){
                int temp = *(arr+j);
                *(arr+j) = *(arr+i);
                *(arr+i) = temp;
            }
        }
    }

    printf("Sorted Array\n");
    for(int i = 0; i < n;i++){
        printf("%d ",*(arr+i));
    }
    printf("\n");
    printf("The Minimum number is : %d\n" ,*(arr + n-1));
    printf("The Maximum number is : %d\n" ,*(arr));
    printf("\n");
    free(arr);

    return 0;

}