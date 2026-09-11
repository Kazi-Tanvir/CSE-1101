//Example 1 from the book 

#include<stdio.h>

int main(){

    char in[80];
    char out[] = "Writing was done successfully";
    FILE *output = fopen("data/output.txt","w");
    FILE *input = fopen("data/output.txt","r");
        if(output == NULL || input== NULL){
        printf("unable to open File");
        return 1;
    }
    for (int i = 0; out[i]; i++){
        fputc(out[i],output);
    }
    fclose(output);
    char ch;
    for (int i = 0;((ch = fgetc(input)) != EOF); i++){
        in[i] = ch;
    }
    fclose(input);

    printf("%s\n",in);
    

    
    
}



// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
//     char str[80] = "This is a file system test.\n";
//     FILE *fp;
//     char *p;
//     int i;

//     /* open myfile for output */
//     if((fp = fopen("myfile", "w"))==NULL) {
//         printf("Cannot open file.\n");
//         exit(1);
//     }

//     /* write str to disk */
//     p = str;
//     while(*p) {
//         if(fputc(*p, fp)==EOF) {
//             printf("Error writing file.\n");
//             exit(1);
//         }
//         p++;
//     }
//     fclose(fp);

//     /* open myfile for input */
//     if((fp = fopen("myfile", "r"))==NULL) {
//         printf("Cannot open file.\n");
//         exit(1);
//     }

//     /* read back the file */
//     for(;;) {
//         i = fgetc(fp);
//         if(i == EOF) break;
//         printf("%c",i);
//     }
//     fclose(fp);

//     return 0;
// }