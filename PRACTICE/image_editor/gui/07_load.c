#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    unsigned short bfType;
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;
} BMPFileHeader;

typedef struct {
    unsigned int   biSize;
    int            biWidth;
    int            biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int   biCompression;
    unsigned int   biSizeImage;
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
} BMPInfoHeader;
#pragma pack(pop)

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef struct {
    int width;
    int height;
    Pixel *data;
} Image;

Image *create_image(int width, int height) {
    if (width <= 0 || height <= 0) return NULL;
    Image *img = (Image *)malloc(sizeof(Image));
    if (!img) return NULL;

    img->width  = width;
    img->height = height;
    img->data   = (Pixel *)calloc((size_t)width * height, sizeof(Pixel));
    if (!img->data) {
        free(img);
        return NULL;
    }
    return img;
}

void free_image(Image *img) {
    if (!img) return;
    if (img->data) {
        free(img->data);
        img->data = NULL;
    }
    free(img);
}

Image *load_bmp(const char *filename) {
    if (!filename) return NULL;

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    BMPFileHeader file_header;
    if (fread(&file_header, sizeof(BMPFileHeader), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    if (file_header.bfType != 0x4D42) {
        fprintf(stderr, "Error: Not a valid BMP file (missing 'BM').\n");
        fclose(file);
        return NULL;
    }

    BMPInfoHeader info_header;
    if (fread(&info_header, sizeof(BMPInfoHeader), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    if (info_header.biBitCount != 24 || info_header.biCompression != 0) {
        fprintf(stderr, "Error: Only uncompressed 24-bit BMP files are supported.\n");
        fclose(file);
        return NULL;
    }

    int width = info_header.biWidth;
    int height = info_header.biHeight;
    int is_top_down = 0;

    if (height < 0) {
        height = -height;
        is_top_down = 1;
    }

    Image *img = create_image(width, height);
    if (!img) {
        fclose(file);
        return NULL;
    }

    int padding = (4 - ((width * 3) % 4)) % 4;

    if (fseek(file, (long)file_header.bfOffBits, SEEK_SET) != 0) {
        free_image(img);
        fclose(file);
        return NULL;
    }

    for (int y = 0; y < height; y++) {
        int target_row = is_top_down ? y : (height - 1 - y);

        for (int x = 0; x < width; x++) {
            unsigned char bgr[3];
            if (fread(bgr, 1, 3, file) != 3) {
                free_image(img);
                fclose(file);
                return NULL;
            }

            int idx = target_row * width + x;
            img->data[idx].b = bgr[0];
            img->data[idx].g = bgr[1];
            img->data[idx].r = bgr[2];
        }

        if (padding > 0) {
            fseek(file, padding, SEEK_CUR);
        }
    }

    fclose(file);
    return img;
}

int main(int argc, char **argv) {
    const char *filepath = (argc > 1) ? argv[1] : "lena.bmp";

    Image *img = load_bmp(filepath);
    if (!img) {
        fprintf(stderr, "Could not load image: %s\n", filepath);
        return EXIT_FAILURE;
    }

    printf("Successfully loaded: %s\n", filepath);
    printf("Dimensions: %d x %d pixels\n", img->width, img->height);

    int target_x = 100;
    int target_y = 100;

    if (target_x < img->width && target_y < img->height) {
        int idx = target_y * img->width + target_x;
        Pixel p = img->data[idx];
        printf("Pixel at (%d, %d) -> R: %u, G: %u, B: %u\n",
               target_x, target_y, p.r, p.g, p.b);
    } else {
        printf("Coordinate (%d, %d) is out of bounds for this image.\n", target_x, target_y);
    }

    free_image(img);
    return EXIT_SUCCESS;
}