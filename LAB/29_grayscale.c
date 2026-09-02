#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
#pragma pack(push, 1)
typedef struct {
    unsigned short type;        
    unsigned int   size;       
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int   offset;     
} BMPHeader;

typedef struct {
    unsigned int   size;        
    int            width;       
    int            height;      
    unsigned short planes;      
    unsigned short bpp;         
    unsigned int   compression; 
} BMPInfoHeader;
#pragma pack(pop)

typedef struct{
    unsigned char  RED;
    unsigned char GREEN;
    unsigned char BLUE;
} RGB;

#pragma pack(pop)

int main(){
    FILE *input = fopen("data/lena.bmp","rb");
    FILE *output = fopen("data/gray_lena.bmp","wb");

    if (!input || !output) {
        printf("Error: Could not open input file.\n");
        return 1;
    } 
    BMPHeader header;
    BMPInfoHeader info;


    fread(&header,sizeof(BMPHeader),1,input);
    if (header.type != 0x4D42) {
        printf("NOT A BMP FILE !\n");
        fclose(input);
        return 0;
    }
    fread(&info,sizeof(BMPInfoHeader),1,input);
    
    fwrite(&header,sizeof(BMPHeader),1,output);
    fwrite(&info,sizeof(BMPInfoHeader),1,output);

    int width = info.width;
    int height = info.height;
    
    printf("%d \n",height );
    printf("%d",width);

    fseek(input ,header.offset ,SEEK_SET);
    fseek(output ,header.offset ,SEEK_SET);
    for(int h = 0 ; h < height ; h++){
        RGB pixel;
        for(int w = 0 ; w < width ; w++){
            fread(&pixel,sizeof(RGB),1,input);

            int gray = 0.299*pixel.RED + 0.587*pixel.GREEN + 0.114*pixel.BLUE;
            pixel.RED = gray;
            pixel.GREEN = gray;
            pixel.BLUE = gray;

            fwrite(&pixel,sizeof(RGB),1,output);

        }
    }

    fclose(input);
    fclose(output);
}