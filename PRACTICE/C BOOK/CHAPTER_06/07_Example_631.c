#include <ctype.h>
#include <stdio.h>

int main(void)
{
    char str[80], *p;

    printf("Enter a string: ");
    fgets(str,sizeof(str),stdin);

    p = str;
    for(;*p;){
        *p = toupper(*p);
        *p++;
    }
    printf("%s\n",str); /* uppercase string */
        
    p = str;
    for(;*p;){
        *p = tolower(*p);
        *p++;
    }
    printf("%s\n", str); /* lowercase string */

    return 0;
}