#include<stdio.h>

int main(){
    int mday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day , month , year, invalid = 0;

    printf("Input:\n");
    scanf("%d %d %d", &day, &month, &year);

    if(year < 0) invalid = 1;
    if(month > 12 || month < 1) invalid = 1;
    if(month == 2 && year%100 != 0 && (year%4 == 0 || year%400 == 0)) mday[1] = 29;
    if(day > mday[month - 1] || day < 1) invalid = 1;

    if(invalid) printf("INVALID");
    else printf("VALID");
    
    return 0;
}