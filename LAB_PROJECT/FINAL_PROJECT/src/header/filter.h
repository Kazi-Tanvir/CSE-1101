#ifndef FILTER_H
#define FILTER_H
#include "image.h"

void grayscale(Image *img);
void brightness(Image *img, int brightness);
void inversion(Image *img);
void horizontalFlip(Image *img);
void verticalFlip(Image *img);

Image *rotate90(const Image *img);
Image *crop(const Image *img, int x1, int y1, int x2, int y2);
Image *blur(const Image *img);
Image *sharpen(const Image *img);

#endif