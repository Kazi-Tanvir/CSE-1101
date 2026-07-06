#include<stdio.h>

int factorial(int n){
    if (n == 0) return 1;
    return n * factorial(n-1);
}
int nCr(int n, int r ){
    return factorial(n) / ( factorial(r) * factorial(n-r));
}
int main(){
    int line;
    scanf("%d", &line);
    for(int n =0 ; n < line ;n++ ){
        for(int i = line - n - 1 ; i > 0 ; i-- ){
            printf(" ");
        }
        for (int r = 0 ; r <= n ; r++){
            printf("%d ",nCr(n , r));
        }
        printf("\n");
    }
    return 0;
}