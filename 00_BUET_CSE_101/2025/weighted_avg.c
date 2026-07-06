#include <stdio.h>
#include<math.h>

int main() {

    long x = sizeof(long);
    long y = pow(2,8*(x));
    printf("%ld",(y-1));

}   