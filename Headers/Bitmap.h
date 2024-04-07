#ifndef PROJECT_2_BITMAP_H
#define PROJECT_2_BITMAP_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
typedef struct tagBITMAPFILEHEADER {
    WORD  bfType;
    DWORD bfSize;
    WORD  bfReserved1;
    WORD  bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;

// https://docs.microsoft.com/pl-pl/previous-versions/dd183376(v=vs.85)
typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG  biWidth;
    LONG  biHeight;
    WORD  biPlanes;
    WORD  biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct{
    int R;
    int G;
    int B;
} PIXEL;

typedef struct{
    BITMAPINFOHEADER *BMIH;
    BITMAPFILEHEADER *BMFH;
    PIXEL **pixels;
} BITMAPDATA;

extern void print_file_header(BITMAPFILEHEADER *BMFH);
extern void print_info_header(BITMAPINFOHEADER *BMIH);
extern PIXEL **create_pixel_array(size_t height, size_t width);
extern bool destroy_pixel_array(PIXEL **pixels, size_t height);
extern BITMAPDATA *create_bitmapdata(BITMAPFILEHEADER *BMFH, BITMAPINFOHEADER *BMIH);
bool destroy_bitmapdata(BITMAPDATA *btd);
extern int get_padding(BITMAPINFOHEADER *BMIH);
extern unsigned char **create_hex_array(size_t height, size_t width);
extern unsigned char **create_hex_array_from_pixels(PIXEL **pixels, size_t height, size_t width);
extern bool destroy_hex_array(unsigned char **hex_array, size_t height);
extern PIXEL **create_pixel_array_from_hex(unsigned char **hex_array, size_t height, size_t width);

#endif //PROJECT_2_BITMAP_H
