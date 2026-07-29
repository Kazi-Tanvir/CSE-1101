    #include<stdio.h>

    void get_min_max(int *arr, int size, int *min ,int *max){
        for(int i = 0 ;i < size-1; i++){
            for(int j = 0; j < size - i - 1;j++){
                if(*(arr + j) > *(arr + j + 1)){
                    int temp = *(arr + j);
                    *(arr + j) = *(arr + j + 1);
                    *(arr + j + 1) = temp;
                }
            }
        }
        *min = *(arr);
        *max = *(arr + size -1);
    }

    int main(){
        int size;
        int min ,max;
        scanf("%d",&size);

        int arr[size];
        for(int i = 0; i < size; i++){
            scanf("%d",arr + i);
        }

        get_min_max(arr, size, &min, &max);
        printf("min:%d\nmax:%d\n",min,max);
        
        return 0; 
    }