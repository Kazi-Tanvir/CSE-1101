#include<stdio.h>

int main(){

    int count[100][10];

    *(*(count+44)+8) = 99;
    printf("%d %d %d ",count[44][8],*(*(count+44)+8),*(&count[0][0] + 44*10 + 8));
}