#include<stdio.h>

int add(int a,int b){
    return a + b;
}

int sub(){
    return a - b;
}

int mul(){
    return a*b;
}

int div(){
    return a/b;
}

int main(){
    char choice;
    int a, b;

    printf("1. Add\n2. Sub\n3. Mul\n4. Div\n");
    printf("Exit by entering x");
    scanf("%c", &choice);
    for(int i = 0 ; c!=x;i++){
        printf("Enter a and b: ");
        scanf("%d %d", &a, &b);
    switch(choice){
        case 'a':
            printf("Result: %d\n", add(a,b));
            break;
        case 's':
            printf("Result: %d\n", sub(a,b));
            break;
        case 'm':
            printf("Result: %d\n", mul(a,b));
            break;
        case 'd':
            printf("Result: %d\n", div(a,b));
            break;
        default:
            printf("Invalid choice\n");
        }
}
    return 0;
}