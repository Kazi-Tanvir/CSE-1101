#include<stdio.h>
#include<stdlib.h>

char *p[] = {
    "Input exceeds field width",
    "Out of range",
    "Printer not turned on",
    "Paper out",
    "Disk full",
    "Disk write error"
};

void error(int err_num)
{
    printf(p[err_num]);
}

int main(int argC, char *argV[]){
    error(atoi(argV[1]));
    return 0;
}