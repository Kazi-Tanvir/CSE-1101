#include<stdio.h>
#include<math.h>

int main(){
    int num ; 
    printf("Enter a Positive Number : ");
    scanf("%d",&num);
    if (num < 0){
        printf("Please enter a positive number");
        return 0;
    }
    int isPrime = 1;
    for(int i = 2 ; i <sqrt(num);i++ ){
        if( num == 0 || num == 1 ||num % i == 0) {
            isPrime = 0;
            break;
        }
    }
    isPrime == 1? printf("IsPrime"):printf("Not Prime");
    return 0;
}
