#include<stdio.h>

int array_sum(const int *start , const int *end){
    int sum = 0;
    for(int i = 0; start != end; i++){
        sum += *start ;
        start++;
    }
    return sum;
}

int main(){
    int arr[10] = { 1,2,3,4,5,6,7,8,9,10};
    int sum = array_sum(arr , arr + 9);

    printf("%d",sum);
}