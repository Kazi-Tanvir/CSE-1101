// 6. Reverse String
// Reference: LeetCode #344 — Reverse String (Easy)
// Task: Write a function that reverses a string in-place. The input is given as an array of characters char* s.
// C Signature: void reverseString(char* s, int sSize)
// Pointer Concept: Two pointers (left and right) moving toward each other.
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