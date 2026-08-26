#ifndef IMAGE_H
#define IMAGE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef struct {
    int width;
    int height;
    Pixel *data;
} Image;

Image *create_image(int width,int height);
void free_image(Image *img);
Image *clone_image(const Image *img);

Image *load_bmp(const char *filename);
int save_bmp(const char *filename, const Image *img);

#endif