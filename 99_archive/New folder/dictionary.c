#include <stdio.h>
#include <string.h>

int main() {
    char s1[50], s2[50];

    printf("Enter first string: ");
    scanf("%s", s1);
    printf("Enter second string: ");
    scanf("%s", s2);

    int result = strcmp(s1, s2);

    if (result < 0) {
        printf("%s comes before %s\n", s1, s2);
    } else if (result > 0) {
        printf("%s comes before %s\n", s2, s1);
    } else {
        printf("Both strings are the same!\n");
    }

    return 0;
}
