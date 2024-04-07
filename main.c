#include <stdio.h>
#include <stdlib.h>
#include "Headers/Bitmap.h"
#include "Headers/FileProcessing.h"
#include "Headers/Mandelbrot.h"



int main(int argc, char **argv) {
    if(argc != 4) {
        return 1;
    }
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    char *output = argv[3];

    BITMAPINFOHEADER *BMIH = create_bitmapinfoheader(width, height);
    if(BMIH == NULL) {
        return 1;
    }

    BITMAPFILEHEADER *BMFH = create_bitmapfileheader((int) (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + width*height*3));
    if(BMFH == NULL) {
        return 1;
    }

    PIXEL **pixels = create_pixel_array(height, width);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            double real = map_value(x, 0, width, -2.0, 1.0);
            double imag = map_value(y, 0, height, -1.0, 1.0);
            int value = mandelbrot(real, imag);
            int color = (int)(255.0 * value / MAX_ITERATIONS);
            set_pixel(pixels, x, y, color, color, color);
        }
    }

    FILE *file = create_file(output);
    if(file == NULL) {
        return 1;
    }

    if (!write_to_file(file, BMIH, BMFH, pixels)) {
        return 1;
    }

    close_file(file);
    destroy_pixel_array(pixels, height);
    free(BMFH);
    free(BMIH);
    return 0;
}
