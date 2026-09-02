#include<stdio.h>
#include<string.h>
#include<math.h>
int ASCII_value(char word[]){
    int value = 0;
    for (int i = 0; i < strlen(word); i++)  value += word[i] ;
    return value;
}
int main(){
    char word1[100] , word2[100];
    scanf("%s",word1);
    scanf("%s",word2);
    int result = strcmp(word1 , word2);
    if(result == 0) printf("\n%s\n%s\nThey are same word. \n",word1,word2);
    if (result < 0) printf("\n%s\n%s\n ",word1,word2);
    if(result > 0) printf("\n%s\n%s\n ",word2,word1);
    int num = fabs(ASCII_value(word1) - ASCII_value(word2));
    printf("\nASCII value Difference : %d",num);
    return 0;
}