#include <stdio.h>

int sum_digits(int n) {
    int sum = 0;
    for(int i = 0 ; n > 0 ; i++) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int rec_sum(int n) {
    if (n < 10) {
        return n;
    }
    return rec_sum(sum_digits(n));
}

int main() {
    int n;
    scanf("%d", &n) ;
        printf("%d\n", rec_sum(n));
    
    return 0;
}
