#include<stdio.h>

void function(int *num){
    *num = -1 ;
}

int main(){
    int num = 5;
    
    printf("Before : %d\n",num);
    function(&num);
    printf("After : %d\n",num);
}