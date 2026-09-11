#include <stdio.h>
#include <string.h>

char *p[][2] = {
    "Red Delicious", "red",
    "Golden Delicious", "yellow",
    "Winesap", "red",
    "Gala", "reddish orange",
    "Lodi", "green",
    "Mutsu", "yellow",
    "Cortland", "red",
    "Jonathan", "red",
    "", "" /* terminate the table with null strings */
};

int main(void){
    char name[80];
    printf("Enter the name of the apple : ");
    scanf(" %[^\n]",name);
    for(int i = 0; *p[i][0];i++)
        if(!strcmp(name,p[i][0]))
            printf("%s",p[i][1]);
    return 0;

}