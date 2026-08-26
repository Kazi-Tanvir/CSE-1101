/* test_filters.c (temporary test) */
#include "image.h"
#include "filter.h"
#include <stdio.h>

int main(void) {
    Image *img = load_bmp("src/lena.bmp");
    if (!img) return 1;

    /* Test grayscale */
    Image *backup = clone_image(img);
    apply_grayscale(img);
    save_bmp("test_grayscale.bmp", img);
    printf("Saved test_grayscale.bmp\n");

    /* Test inversion on original */
    apply_inversion(backup);
    save_bmp("test_inverted.bmp", backup);
    printf("Saved test_inverted.bmp\n");

    /* Test rotation */
    Image *rotated = apply_rotate_90_cw(backup);
    save_bmp("test_rotated.bmp", rotated);
    printf("Saved test_rotated.bmp\n");

    free_image(img);
    free_image(backup);
    free_image(rotated);
    return 0;
}