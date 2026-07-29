#include<stdio.h>

void reverse(int *start, int *end){
    if(start >= end) return ;
    int temp = *end;
    *end = *start;
    *start = temp ;
    reverse(start + 1, end - 1);
}
int main(){
    int N;
    scanf("%d",&N);
    int arr[N];

    for( int i = 0; i < N;i++){
        scanf("%d",arr + i);
    }
    reverse(arr, arr + N - 1);

    for(int i = 0; i < N; i++){
        printf("%d ",*(arr+i));
    }
    
}