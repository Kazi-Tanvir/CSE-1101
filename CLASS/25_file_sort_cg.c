#include <stdio.h>

int main() {
    FILE *input = fopen("data/name_cg.txt", "r");
    FILE *ouput = fopen("data/sorted_cg.txt", "w"); 

    if (input == NULL || ouput == NULL) {
        printf("Unable to open the file\n");
        if (input) fclose(input);
        if (ouput) fclose(ouput);
        return 1;
    }

    int roll[50];
    float cgpa[50];
    char name[50][100];
    int merit[50];

    for (int i = 0; i < 50; i++) {
        fscanf(input, " %d %s %f", &roll[i], name[i], &cgpa[i]);
    }

    for (int i = 0; i < 50; i++) {
        merit[i] = i;
    }

    for (int i = 0; i < 50; i++) {
        for (int j = i + 1; j < 50; j++) {
            if (cgpa[merit[i]] < cgpa[merit[j]]) {
                int temp = merit[i];
                merit[i] = merit[j];
                merit[j] = merit[j];
                merit[j] = temp;
            }
        }
    }

    for (int i = 0; i < 50; i++) {
        fprintf(ouput, "%d %d %s %.2f\n", i + 1, roll[merit[i]], name[merit[i]], cgpa[merit[i]]);
    }

    fclose(input);
    fclose(ouput);

    return 0;
}