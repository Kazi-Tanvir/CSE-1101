#include <stdio.h>

void copyElements(int* arr, int* temp, int right, int k){
    if (k > right) return;
    *(arr+k) = *(temp+k);
    copyElements(arr, temp, right, k + 1);
}

void mergeElements(int* arr, int* temp, int mid, int right, int i, int j, int k){
    if (i > mid && j > right) return;
    if (i > mid) {
        *(temp+k) = *(arr+j);
        mergeElements(arr, temp, mid, right, i, j + 1, k + 1);
    } else if (j > right) {
        *(temp+k) = *(arr+i);
        mergeElements(arr, temp, mid, right, i + 1, j, k + 1);
    } else if (*(arr+i) <= *(arr+j)) {
        *(temp+k) = *(arr+i);
        mergeElements(arr, temp, mid, right, i + 1, j, k + 1);
    } else {
        *(temp+k) = *(arr+j);
        mergeElements(arr, temp, mid, right, i, j + 1, k + 1);
    }
}

void mergeSort(int *arr, int *temp, int left, int right){
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, temp, left, mid);
    mergeSort(arr, temp, mid + 1, right);
    mergeElements(arr, temp, mid, right, left, mid + 1, left);
    copyElements(arr, temp, right, left);
}

int main(){
        int n;
    printf("Enter the length of array :");
    scanf("%d",&n);
    int *arr = (int*) malloc(n * sizeof(int));

    printf("Enter you %d integers :", n);
    for(int i = 0; i < n;i++){
        scanf("%d",arr + i);
    }

    if(arr == NULL) return 0;

    int *temp = (int*) malloc(n * sizeof(int));
    
    mergeSort(arr, temp, 0, n - 1);
    
    printf("Sorted Array: \n");
    for(int i = 0; i < n; i++) printf("%d ", *(arr+i));
    printf("\n");

    free(temp);
    free(arr);
    
    return 0;
}