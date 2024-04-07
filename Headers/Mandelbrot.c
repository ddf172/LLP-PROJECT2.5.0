#include "Mandelbrot.h"

BITMAPFILEHEADER *create_bitmapfileheader(int size) {
    BITMAPFILEHEADER *BMFH = malloc(sizeof(BITMAPFILEHEADER));
    if(BMFH == NULL) {
        return NULL;
    }
    BMFH->bfType = 0x4D42;
    BMFH->bfSize = size;
    BMFH->bfReserved1 = 0;
    BMFH->bfReserved2 = 0;
    BMFH->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    return BMFH;
}

BITMAPINFOHEADER *create_bitmapinfoheader(int width, int height) {
    BITMAPINFOHEADER *BMIH = malloc(sizeof(BITMAPINFOHEADER));
    if(BMIH == NULL) {
        return NULL;
    }
    BMIH->biSize = sizeof(BITMAPINFOHEADER);
    BMIH->biWidth = width;
    BMIH->biHeight = height;
    BMIH->biPlanes = 1;
    BMIH->biBitCount = 24;
    BMIH->biCompression = 0;
    BMIH->biSizeImage = 0;
    BMIH->biXPelsPerMeter = 0;
    BMIH->biYPelsPerMeter = 0;
    BMIH->biClrUsed = 0;
    BMIH->biClrImportant = 0;
    return BMIH;
}

double map_value(double value, double in_min, double in_max, double out_min, double out_max) {
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int mandelbrot(double real, double imag) {
    int n;
    double complex z = 0;
    double complex c = real + imag * I;
    for(n = 0; n < MAX_ITERATIONS; n++) {
        if(cabs(z) > 2.0) {
            break;
        }
        z = z * z + c;
    }
    return n;
}

bool set_pixel(PIXEL **pixels, int x, int y, int r, int g, int b) {
    if(pixels == NULL) {
        return false;
    }
    pixels[y][x].R = r;
    pixels[y][x].G = g;
    pixels[y][x].B = b;
    return true;
}