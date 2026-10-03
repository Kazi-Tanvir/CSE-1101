#include<stdio.h>
#include<string.h>
struct{
    char id[5];
    char password[5];
}file,input;

void encryption(char pass[]){
    int temp = pass[0];
    pass[0]=pass[2];
    pass[2] = temp;

    temp = pass[1];
    pass[1] = pass[3];
    pass[3] = temp;
}

int main(int argc , char *argv[]){
    FILE *fp  =fopen(argv[1],"rb");
    if(!fp){
        printf("Error opening file!");
        return 1;
    }
    
    fscanf(fp, "%s %s", file.id, file.password);
    fclose(fp);

    printf("Enter your user name : ");
    scanf(" %[^\n]", input.id);
    printf("Enter your password : ");
    scanf(" %[^\n]", input.password);

    encryption(input.password);

    if(strcmp(file.id, input.id) == 0 && strcmp(file.password, input.password) == 0){
        printf("Login successful!");
    }else{
        printf("Login failed!");
    }
    
}