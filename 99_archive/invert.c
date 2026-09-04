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
    FILE *input = fopen("lena.bmp","rb");
    FILE *output = fopen("invert.bmp","wb");

    BMPHeader header;
    BMPInfoHeader info;

    fread(&header,sizeof(BMPHeader),1,input);
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
            pixel.RED = 255 - pixel.RED;
            pixel.GREEN = 255 - pixel.GREEN;
            pixel.BLUE = 255 - pixel.BLUE;

            fwrite(&pixel,sizeof(RGB),1,output);

        }
    }

    fclose(input);
    fclose(output);
}