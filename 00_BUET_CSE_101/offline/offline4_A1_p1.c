#include<stdio.h>
void swap(int *a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main(){
    int arr[3];
    int *ptr[3];
    for (int i = 0; i < 3; i++)
    {
        scanf("%d",&arr[i]);
        ptr[i] = &arr[i];
    }
    
    for(int i = 0; i < 3; i++){
        for(int j = i+1 ; j < 3; j++){
            if(arr[i] > arr[j]){
                swap(ptr[i],ptr[j]);
            }
        }
    }

    for(int i = 0; i < 3; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}