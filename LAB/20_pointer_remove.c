
#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    printf("Enter the length of array :");
    scanf("%d",&n);
    int *x = (int*)malloc((n + 1) * sizeof(int));

    
    printf("Enter %d positive integers for x:", n);
    for(int i = 0; i < n;i++){
        scanf("%d",x+i);
    }
    if (x == NULL ) return 0;

    for(int i = 0 ; i< n ; i++){
        for(int j = 0; j < n ; j++){
            if(*(x + i) == *(x + j) && i!=j){
                for(int k = j;k < n;k++ )
                    *(x+k)=*(x + k + 1);
                n--;
            }
        }
    }
    printf("Array X\n");
    for(int i = 0; i < n;i++){
            printf("%d ",*(x + i));
        
    }
    free(x);
    printf("\n");

}