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
        fprintf(stderr, "Error: Not a valid BMP file.\n");
        fclose(file);
        return NULL;
    }

    BMPInfoHeader info_header;
    if (fread(&info_header, sizeof(BMPInfoHeader), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    if (info_header.biBitCount != 24 || info_header.biCompression != 0) {
        fprintf(stderr, "Error: Only uncompressed 24-bit BMP files supported.\n");
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

int save_bmp(const char *filename, const Image *img) {
    if (!img || !img->data || !filename) return 0;

    FILE *file = fopen(filename, "wb");
    if (!file) return 0;

    int width = img->width;
    int height = img->height;
    int padding = (4 - ((width * 3) % 4)) % 4;
    int row_size = width * 3 + padding;
    int data_size = row_size * height;

    BMPFileHeader header;
    header.bfType = 0x4D42;
    header.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + data_size;
    header.bfReserved1 = 0;
    header.bfReserved2 = 0;
    header.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    BMPInfoHeader info_header;
    memset(&info_header, 0, sizeof(BMPInfoHeader));
    info_header.biSize = sizeof(BMPInfoHeader);
    info_header.biWidth = width;
    info_header.biHeight = height;
    info_header.biPlanes = 1;
    info_header.biBitCount = 24;
    info_header.biCompression = 0;
    info_header.biSizeImage = data_size;

    fwrite(&header, sizeof(BMPFileHeader), 1, file);
    fwrite(&info_header, sizeof(BMPInfoHeader), 1, file);

    unsigned char pad[3] = {0, 0, 0};

    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            int idx = y * width + x;
            unsigned char bgr[3] = {
                img->data[idx].b,
                img->data[idx].g,
                img->data[idx].r
            };
            fwrite(bgr, 1, 3, file);
        }
        if (padding > 0) {
            fwrite(pad, 1, padding, file);
        }
    }

    fclose(file);
    return 1;
}

void swap_rb_channels(Image *img) {
    if (!img || !img->data) return;

    int total = img->width * img->height;
    for (int i = 0; i < total; i++) {
        unsigned char temp = img->data[i].r;
        img->data[i].r = img->data[i].b;
        img->data[i].b = temp;
    }
}

int main(int argc, char **argv) {
    const char *input_path = (argc > 1) ? argv[1] : "lena.bmp";
    const char *output_path = "swapped.bmp";

    Image *img = load_bmp(input_path);
    if (!img) {
        fprintf(stderr, "Failed to load: %s\n", input_path);
        return EXIT_FAILURE;
    }

    swap_rb_channels(img);

    if (save_bmp(output_path, img)) {
        printf("Channels swapped successfully.\nSaved result to: %s\n", output_path);
    } else {
        fprintf(stderr, "Failed to write to %s\n", output_path);
    }

    free_image(img);
    return EXIT_SUCCESS;
}   