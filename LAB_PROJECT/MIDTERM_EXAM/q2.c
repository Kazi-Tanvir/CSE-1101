#include <stdio.h>

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[j] > arr[i]) {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        int counter = 0;
        for (int j = i; j < N; j++) {
            if (arr[i] == arr[j]) {
                counter++;
            }
        }
        
        if (i == 0 || arr[i] != arr[i - 1]) {
            printf("%d: ", arr[i]);
            for (int k = 0; k < counter; k++) {
                printf("*");
            }
            printf("\n");
        }
    }
    
    return 0;
}
