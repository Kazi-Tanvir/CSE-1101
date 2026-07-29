#include<stdio.h>
#include<math.h>

void moveZeroes(int* nums, int numsSize , int val) {
    if(numsSize < 1 && numsSize > 10000) return;
    for( int i = 0 ; i < numsSize ; i++){
        if(nums[i]< -pow(2,31) && nums[i] > pow(2,31) - 1) return;
    }
    for(int i = 0; i < numsSize ;i++){
        if(*(nums + i) == val){
            for(int j = i ; j < numsSize ; j++){
                *(nums + j) = *(nums + j + 1);
            }
            *(nums + numsSize - 1) = "";
            i--;
            numsSize--;
        }
    }
}

int main(){
    int n ,val;
    scanf("%d",&n);
    int nums[n];
    int numSize = sizeof(nums)/sizeof(int);
    for(int i = 0 ; i < numSize ; i++){
        scanf("%d",&nums[i]);
    }
    for(int i = 0 ; i < numSize ; i++){
        printf("%d ",nums[i]);
    }
    printf("\n");
    
    scanf("%d",&val);

    moveZeroes(nums,numSize,val);

    for(int i = 0 ; i < numSize ; i++){
        printf("%d ",nums[i]);
    }

}