#include<stdio.h>

int main(){
	int MonthlyDate[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	
	int month , year ;
    
	scanf("%d %d",&month , &year);

	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)){
		MonthlyDate[1] = 29 ;
	}

	if (month < 1 || month > 12) {
        printf("Invalid Month\n");
    } else {
        printf("%d\n" , MonthlyDate[month-1]);
    }
	return 0 ; 
	
      }
