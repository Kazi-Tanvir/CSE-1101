#include<stdio.h>
#include<string.h>

int main(){
    char *p[3]= {"Yes" , "No", "Maybe. Rephrase the question"};
    char question[80];
    scanf(" %[^\n]", question);

    int length = strlen(question);
    int index = length%3;

    printf(p[index]);
}