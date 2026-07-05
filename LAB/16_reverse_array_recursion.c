#include<stdio.h>

int reverse(int arr[],int start,int end){
    if(start >= end) return 0;
    int temp = arr[end];
    arr[end] = arr[start];
    arr[start] = temp ;
    return reverse(arr , start + 1 , end - 1);
}

int main(){
    int arr[5] = { 2,5,6,7,4};
    int size = sizeof(arr)/sizeof(int);
    reverse(size - 1 , 0);
    for (int i = 0; i< size ; i++){
        printf("%d",arr[i]);
    }
    printf("\n")
}