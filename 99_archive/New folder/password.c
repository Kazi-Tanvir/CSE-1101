#include <stdio.h>

int main()
{
    char password[20];
    char confirm_password[20] = "password123";
    int match = 1; 

    printf("Enter your password: ");
    scanf("%19s", password); 

    for(int i = 0; password[i] != '\0' || confirm_password[i] != '\0'; i++)
    {
        if(password[i] != confirm_password[i])
        {
            match = 0; 
            break;      
        }
    }

    if(match == 1)
    {
        printf("Password confirmed!\n");
    }
    else
    {
        printf("Password does not match!\n");
    }
    
    return 0;
}