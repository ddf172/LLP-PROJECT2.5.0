#ifndef PROJECT_2_FILEPROCESSING_H
#define PROJECT_2_FILEPROCESSING_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Bitmap.h"

extern FILE *open_file(char *filename);
extern bool read_file_prop(FILE *file, void *prop, size_t size, size_t number);
extern bool read_file_header(FILE *file, BITMAPFILEHEADER *BMFH);
extern bool read_info_header(FILE *file, BITMAPINFOHEADER *BMIH);
extern bool read_pixels(FILE *file, BITMAPDATA *btd);
extern FILE *create_file(char *filename);
extern bool write_bytes(FILE *file, unsigned char byte, size_t number);
extern bool write_headers(FILE *file, BITMAPFILEHEADER *BMFH, BITMAPINFOHEADER *BMIH);
extern bool write_offset(FILE *file, unsigned int offset);
extern bool write_pixels(FILE *file, PIXEL **pixels,unsigned int height,unsigned int width,unsigned int offset,unsigned int padding,unsigned int bit_count);
extern bool write_to_file(FILE *file, BITMAPINFOHEADER *BMIH, BITMAPFILEHEADER *BMFH,  PIXEL **pixels);
extern bool close_file(FILE *file);

#endif //PROJECT_2_FILEPROCESSING_H
