#include <stdio.h>

void copyElements(int arr[], int temp[], int right, int k){
    if (k > right) return;
    arr[k] = temp[k];
    copyElements(arr, temp, right, k + 1);
}

void mergeElements(int arr[], int temp[], int mid, int right, int i, int j, int k){
    if (i > mid && j > right) return;
    if (i > mid) {
        temp[k] = arr[j];
        mergeElements(arr, temp, mid, right, i, j + 1, k + 1);
    } else if (j > right) {
        temp[k] = arr[i];
        mergeElements(arr, temp, mid, right, i + 1, j, k + 1);
    } else if (arr[i] <= arr[j]) {
        temp[k] = arr[i];
        mergeElements(arr, temp, mid, right, i + 1, j, k + 1);
    } else {
        temp[k] = arr[j];
        mergeElements(arr, temp, mid, right, i, j + 1, k + 1);
    }
}

void mergeSort(int arr[], int temp[], int left, int right){
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, temp, left, mid);
    mergeSort(arr, temp, mid + 1, right);
    mergeElements(arr, temp, mid, right, left, mid + 1, left);
    copyElements(arr, temp, right, left);
}

int main(){
    int arr[] = {75, 90, 40, 85, 60, 55, 100, 35};
    int len = sizeof(arr) / sizeof(arr[0]);
    int temp[len]; 
    
    mergeSort(arr, temp, 0, len - 1);
    
    printf("Sorted Array: \n");
    for(int i = 0; i < len; i++) printf("%d ", arr[i]);
    printf("\n");
    
    return 0;
}