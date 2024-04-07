#ifndef LLP_PROJECT_2_5_0_MANDELBROT_H
#define LLP_PROJECT_2_5_0_MANDELBROT_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <complex.h>
#include "Bitmap.h"

#define MAX_ITERATIONS 100
extern BITMAPINFOHEADER *create_bitmapinfoheader(int width, int height);
extern BITMAPFILEHEADER *create_bitmapfileheader(int size);
extern double map_value(double value, double in_min, double in_max, double out_min, double out_max);
extern int mandelbrot(double real, double imag);
extern bool set_pixel(PIXEL **pixels, int x, int y, int r, int g, int b);

#endif //LLP_PROJECT_2_5_0_MANDELBROT_H
