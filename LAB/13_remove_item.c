#include<stdio.h>

int main(){
    int n;
    printf("Enter the length of array :");
    scanf("%d",&n);
    int x[n];

    //input 
    printf("Enter %d positive integers for x:", n);
    for(int i = 0; i < n;i++){
        scanf("%d",&x[i]);
    }

    for(int i = 0 ; i< n ; i++){
        for(int j = 0; j < n ; j++){
            if(x[i] == x[j] && i!=j){
                for(int k = j;k < n;k++ )
                    x[k]=x[k+1];
                n--;
            }
        }
    }
    printf("Array X\n");
    for(int i = 0; i < n;i++){
            printf("%d ",x[i]);
        
    }
    printf("\n");

}