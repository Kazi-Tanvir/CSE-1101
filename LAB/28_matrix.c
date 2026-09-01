#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 3;
    int cols = 4;

    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        *(matrix + i) = (int *)malloc(cols * sizeof(int));
        if (*(matrix + i) == NULL) {
            printf("Memory allocation failed for row %d!\n", i);
            return 1;
        }
    }

    int count = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(matrix + i) + j) = count++;
        }
    }
    printf("Matrix (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(*(matrix + i));
    }
    free(matrix);

    return 0;
}