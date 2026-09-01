#include <stdio.h>

union Data {
    char x;
    struct {
        unsigned char a:1;
        unsigned char b:1;
        unsigned char c:1;
        unsigned char d:1;
        unsigned char e:1;
        unsigned char f:1;
        unsigned char g:1;
        unsigned char h:1;
    } Bits;
};

char enryption_bit(char x) {
    union Data d;
    d.x = x;
    int temp = d.Bits.a;
    d.Bits.a = d.Bits.b;
    d.Bits.b = d.Bits.c;
    d.Bits.c = d.Bits.d;
    d.Bits.d = d.Bits.e;
    d.Bits.e = d.Bits.f;
    d.Bits.f = d.Bits.g;
    d.Bits.g = d.Bits.h;
    d.Bits.h = temp;
    return d.x;
}



int main() {
    char ch;

    FILE *input = fopen("data/name_cg.txt","r");
    FILE *output = fopen("data/name_cg_encrypted.txt","w");
    if(input == NULL || output == NULL){
        printf("File not found\n");
        return 1;
    }
    while((ch=fgetc(input)) != EOF){
        fprintf(output,"%c",enryption_bit(ch));
    }

    fclose(input);
    fclose(output);
    
    return 0;

}