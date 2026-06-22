#include<stdio.h>

int main(){
    int temp[7];
    int sum = 0;
    printf("Enter the temperature of 7 days: ");
    for(int i = 0;i<7;i++){
        scanf(" %d", &temp[i]);
        sum += temp[i];
    }
    int avg = sum/7;
    printf("Average temperature: %d", avg);
    return 0;
}