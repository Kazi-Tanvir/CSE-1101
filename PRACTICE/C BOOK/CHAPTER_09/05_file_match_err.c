//Example 4 from the book 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *from, *to;
    char ch_from, ch_to;
    int match = 1;
    unsigned long byte; 

    /* see if correct number of command line arguments */
    if(argc!=3) {
        printf("Usage: copy <source> <destination>\n");
        exit(1);
    }

    /* open source file */
    if((from = fopen(argv[1], "rb"))==NULL) {
        printf("Cannot open source file.\n");
        exit(1);
    }

    /* open destination file */
    if((to = fopen(argv[2], "rb"))==NULL) {
        printf("Cannot open destination file.\n");
        exit(1);
    }

    /* copy the file */
    while(!feof(from)||!feof(to)) {
        ch_from = fgetc(from);
        ch_to = fgetc(to);
        if(ferror(from) || ferror(to)) {
            printf("Error reading  file.\n");
            exit(1);
        }
        if(ch_from != ch_to){
            match = 0;
            break;
        }
        byte++;
    }
    match?printf("Files are the same.\n"):printf("char are not smae at byte no. %lu\n", byte);

    if(fclose(from)==EOF) {
        printf("Error closing source file.\n");
        exit(1);
    }

    if(fclose(to)==EOF) {
        printf("Error closing destination file.\n");
        exit(1);
    }

    return 0;
}