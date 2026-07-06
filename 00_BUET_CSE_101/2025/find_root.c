#include<stdio.h> 
#include<math.h> 


float func(float x){
    return pow(x , 5) + 3*x*x -10;
}
float dif_func(float x){
    return 5*pow(x,4)+6*x;
}

int main (){
    float guess;
    printf("Enter your guess : ");
    scanf("%f",&guess);
    float x = 0;
    for(int i = 0 ; ;i++){
        if(guess == 0) guess = 1;
        x = guess - func(guess)/dif_func(guess);
        if(fabs(x-guess) <=0.00001 ) break;
        guess = x;
    }
    printf("%f\n",x);
    return 0;
}