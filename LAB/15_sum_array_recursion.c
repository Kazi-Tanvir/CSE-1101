#include<stdio.h>

int sum(int arr[], int n){
    int(n < 0) return 0;
    return arr[n] + sum(arr ,n-1);
}

int main(){
    int arr[5] = { 2,5,6,7,4};
    int size = sizeof(arr)/sizeof(int);
    printf("The Summ is %d \n" , sum(arr , size -1));
}