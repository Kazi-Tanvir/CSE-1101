#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_strcat(char *x, const char *y) {
    while (*x != '\0') {
        x++;
    }

    while (*y != '\0') {
        *x = *y;
        x++;
        y++;
    }

    *x = '\0';
}

int main() {
    int n, m;

    printf("Enter max length of first string: ");
    scanf("%d", &n);

    printf("Enter max length of second string: ");
    scanf("%d", &m);

    char *x = malloc((n + m + 1) * sizeof(char));
    char *y = malloc((m + 1) * sizeof(char));

    if (x == NULL || y == NULL) return 0;
    

    printf("Enter first string: ");
    scanf("%s", x);

    printf("Enter second string: ");
    scanf("%s", y);

    my_strcat(x, y);

    printf("Merged string: %s\n", x);

    free(x);
    free(y);

    return 0;
}