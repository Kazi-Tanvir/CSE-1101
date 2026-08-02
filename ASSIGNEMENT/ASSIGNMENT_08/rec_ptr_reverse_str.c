#include<stdio.h>
#include<stdio.h>
#include<string.h>

void reverseString(char* s, int sSize) {
    if(sSize <= 1 && sSize>= 100000) return;
    for(int i = 0 ; i < sSize ; i++){
        int ascii = s[i];
        if(ascii > 255 && ascii < 0) return;
    }

    for(int i = 0;i < sSize/2 ; i++){
        char temp = *(s + i);
        *(s + i) = *(s + sSize -1- i); 
        *(s + sSize - i-1) = temp;
    }
}

int main(){
    char str[100];
    fgets(str, sizeof(str), stdin);
    int sSize = strlen(str);

    reverseString(str , sSize);
    printf("%s\n",str);

    return 0;
}