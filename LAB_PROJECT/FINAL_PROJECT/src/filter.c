#include "filter.h"

static inline unsigned char clamp(int val) {
    if (val < 0) return 0;
    if (val > 255) return 255;
    return (unsigned char)val;
}

void grayscale(Image *img) {
    if (!img || !img->data) return;

    int total = img->width * img->height;
    for (int i = 0; i < total; i++) {
        unsigned char gray = (unsigned char)(0.299 * img->data[i].r + 0.587 * img->data[i].g + 0.114 * img->data[i].b);
        img->data[i].r = gray;
        img->data[i].g = gray;
        img->data[i].b = gray;
    }
}

void brightness(Image *img, int brightness) {
    if (!img || !img->data) return;

    int total = img->width * img->height;
    for (int i = 0; i < total; i++) {
        img->data[i].r = clamp(img->data[i].r + brightness);
        img->data[i].g = clamp(img->data[i].g + brightness);
        img->data[i].b = clamp(img->data[i].b + brightness);
    }
}

void inversion(Image *img) {
    if (!img || !img->data) return;

    int total = img->width * img->height;
    for (int i = 0; i < total; i++) {
        img->data[i].r = 255 - img->data[i].r;
        img->data[i].g = 255 - img->data[i].g;
        img->data[i].b = 255 - img->data[i].b;
    }
}

void horizontalFlip(Image *img) {
    if (!img || !img->data) return;

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width / 2; x++) {
            int left  = y * img->width + x;
            int right = y * img->width + (img->width - 1 - x);

            Pixel temp       = img->data[left];
            img->data[left]  = img->data[right];
            img->data[right] = temp;
        }
    }
}

void verticalFlip(Image *img) {
    if (!img || !img->data) return;

    for (int y = 0; y < img->height / 2; y++) {
        for (int x = 0; x < img->width; x++) {
            int top    = y * img->width + x;
            int bottom = (img->height - 1 - y) * img->width + x;

            Pixel temp        = img->data[top];
            img->data[top]    = img->data[bottom];
            img->data[bottom] = temp;
        }
    }
}

Image *rotate90(const Image *img){
    if(!img || !img->data) return NULL;

    Image *rotated = create_image(img->height, img->width);
    if(!rotated) return NULL;

    for(int y = 0; y < img->height; y++){
        for(int x = 0; x < img->width; x++){
            int srcIdx = y * img->width + x;
            int dstIdx = x * img->height + (img->height - 1 - y);

            rotated->data[dstIdx] = img->data[srcIdx];
        }
    }
    return rotated;
}

Image *crop(const Image *img, int x1, int y1, int x2, int y2){
    if(!img || !img->data) return NULL;

    if(x1 < 0) x1 = 0;
    if(y1 < 0) y1 = 0;
    if(x2 >= img->width) x2= img->width-1;
    if(y2 >= img->height) y2 = img->height-1;

    if(x1 > x2 || y1 > y2) return NULL;

    Image *cropped = create_image(x2-x1+1, y2-y1+1);
    if(!cropped) return NULL;

    for(int y=y1; y<=y2; y++){
        for(int x = x1; x<=x2; x++){
            int imgIndex = y*img->width+x;
            int croppedIndex = (y-y1)*cropped->width+(x-x1);
            cropped->data[croppedIndex] = img->data[imgIndex];
        }
    }
    return cropped;
}


Image *blur(const Image *img){
    if(!img || !img->data) return NULL;

    Image *blured = create_image(img->width,img->height);
    if(!blured) return NULL;

    for(int y = 0 ; y < img->height; y++){
        for(int x = 0 ; x < img->width; x++){
            int r_sum =0;
            int g_sum = 0;
            int b_sum = 0;
            int count =0;

            for(int dy = -1; dy<=1; dy++){
                for(int dx = -1; dx<=1; dx++){
                    int nx = x+dx;
                    int ny = y+dy;

                    if(nx>=0 && nx<img->width && ny>=0 && ny<img->height){
                        int idx = ny*img->width + nx;
                        r_sum += img->data[idx].r;
                        g_sum += img->data[idx].g;
                        b_sum += img->data[idx].b;
                        count++;
                    }
                }
            }

            int idx = y*img->width + x;
            blured->data[idx].r = clamp(r_sum/count);
            blured->data[idx].g = clamp(g_sum/count);
            blured->data[idx].b = clamp(b_sum/count);
        }
    }
    return blured;
}

Image *sharpen(const Image *img){
    if(!img || !img->data) return NULL;

    Image *sharpened = create_image(img->width, img->height);
    if(!sharpened) return NULL;

    int kernel[3][3] = {{0,-1,0},{-1,5,-1},{0,-1,0}};   
    
    for(int y=0; y<img->height; y++){
        for(int x=0; x<img->width; x++){
            if(y==0||y==img->height-1||x==0||x==img->width-1){
                int idx = y*img->width + x;
                sharpened->data[idx] = img->data[idx];
                continue;
            }

            int r_sum =0;
            int g_sum =0;
            int b_sum =0;
            
            for(int dy = -1; dy<=1; dy++){
                for(int dx = -1; dx<=1; dx++){
                    int nx = x+dx;
                    int ny = y+dy;
                    
                    int idx = ny*img->width+nx;
                    r_sum += img->data[idx].r*kernel[dy+1][dx+1];
                    g_sum += img->data[idx].g*kernel[dy+1][dx+1];
                    b_sum += img->data[idx].b*kernel[dy+1][dx+1];
                }
            }

            int idx = y*img->width+x;
            sharpened->data[idx].r = clamp(r_sum);
            sharpened->data[idx].g = clamp(g_sum);
            sharpened->data[idx].b = clamp(b_sum);
        }
    }
    return sharpened;
}
