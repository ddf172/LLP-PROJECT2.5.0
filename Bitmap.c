#include "Headers/Bitmap.h"

void print_file_header(BITMAPFILEHEADER *BMFH){
    if (BMFH == NULL){
        return;
    }
    printf("BITMAP FILE HEADER\n");
    printf("bfType: ox%x\n", BMFH->bfType);
    printf("bfSize: %d\n", BMFH->bfSize);
    printf("bfReserved1: %d\n", BMFH->bfReserved1);
    printf("bfReserved2: %d\n", BMFH->bfReserved2);
    printf("bfOffBits: %d\n", BMFH->bfOffBits);
}

void print_info_header(BITMAPINFOHEADER *BMIH){
    if (BMIH == NULL){
        return;
    }
    printf("BITMAP INFO HEADER\n");
    printf("biSize: %d\n", BMIH->biSize);
    printf("biWidth: %d\n", BMIH->biWidth);
    printf("biHeight: %d\n", BMIH->biHeight);
    printf("biPlanes: %d\n", BMIH->biPlanes);
    printf("biBitCount: %d\n", BMIH->biBitCount);
    printf("biCompression: %d\n", BMIH->biCompression);
    printf("biSizeImage: %d\n", BMIH->biSizeImage);
    printf("biXPelsPerMeter: %d\n", BMIH->biXPelsPerMeter);
    printf("biYPelsPerMeter: %d\n", BMIH->biYPelsPerMeter);
    printf("biClrUsed: %d\n", BMIH->biClrUsed);
    printf("biClrImportant: %d\n", BMIH->biClrImportant);
}

PIXEL **create_pixel_array(size_t height, size_t width){
    PIXEL **temp = (PIXEL **) malloc(sizeof(PIXEL *)*height);
    if (temp == NULL){
        return NULL;
    }
    for (int i=0; i<height; i++){
        PIXEL *row = (PIXEL *)calloc(width, sizeof(PIXEL));
        if (row == NULL){
            for (int j=0; j<i; j++){
                free(temp[j]);
            }
            free(temp);
            return NULL;
        }
        temp[i] = row;
        row = NULL;
    }
    return temp;
}

bool destroy_pixel_array(PIXEL **pixels, size_t height){
    if (pixels == NULL){
        return false;
    }
    for (int i=0; i<height; i++){
        free(pixels[i]);
    }
    free(pixels);
    return true;
}

BITMAPDATA *create_bitmapdata(BITMAPFILEHEADER *BMFH, BITMAPINFOHEADER *BMIH){
    BITMAPDATA *btd = malloc(sizeof(BITMAPDATA));
    if (btd == NULL || BMFH == NULL || BMIH == NULL){
        return NULL;
    }
    btd->BMFH = BMFH;
    btd->BMIH = BMIH;
    PIXEL **temp = create_pixel_array(BMIH->biHeight, BMIH->biWidth);
    if (temp == NULL) {
        free(btd);
        return NULL;
    }
    btd->pixels = temp;
    temp = NULL;
    return btd;
}

bool destroy_bitmapdata(BITMAPDATA *btd){
    if (btd == NULL){
        printf("btd is NULL error\n");
        return false;
    }
    if (btd->pixels != NULL) {
        if (btd->BMIH == NULL){
            printf("BMIH is NULL error\n");
            return false;
        }
        destroy_pixel_array(btd->pixels, btd->BMIH->biHeight);
    }
    if (btd->BMFH != NULL){
        free(btd->BMFH);
    }
    if (btd->BMIH != NULL){
        free(btd->BMIH);
    }
    free(btd);
    return true;
}

int get_padding(BITMAPINFOHEADER *BMIH){
    if (BMIH == NULL){
        return -1;
    }
    return ((BMIH->biBitCount * BMIH->biWidth + 31) / 32) * 4 - BMIH->biWidth * (BMIH->biBitCount/8);
}

unsigned char **create_hex_array(size_t height, size_t width){
    unsigned char **temp = (unsigned char **) malloc(sizeof(unsigned char *)*height);
    if (temp == NULL){
        return NULL;
    }
    for (int i=0; i<height; i++){
        unsigned char *row = (unsigned char *)calloc(width*3, sizeof(unsigned char));
        if (row == NULL){
            for (int j=0; j<i; j++){
                free(temp[j]);
            }
            free(temp);
            return NULL;
        }
        temp[i] = row;
        row = NULL;
    }
    return temp;
}

unsigned char **create_hex_array_from_pixels(PIXEL **pixels, size_t height, size_t width){
    unsigned char **temp = create_hex_array(height, width);
    if (temp == NULL){
        return NULL;
    }
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            temp[i][3*j] = pixels[i][j].B;
            temp[i][3*j+1] = pixels[i][j].G;
            temp[i][3*j+2] = pixels[i][j].R;
        }
    }
    return temp;
}

bool destroy_hex_array(unsigned char **hex_array, size_t height){
    if (hex_array == NULL){
        return false;
    }
    for (int i=0; i<height; i++){
        free(hex_array[i]);
    }
    free(hex_array);
    return true;
}

PIXEL **create_pixel_array_from_hex(unsigned char **hex_array, size_t height, size_t width){
    PIXEL **temp = create_pixel_array(height, width);
    if (temp == NULL){
        return NULL;
    }
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            temp[i][j].B = hex_array[i][3*j];
            temp[i][j].G = hex_array[i][3*j+1];
            temp[i][j].R = hex_array[i][3*j+2];
        }
    }
    return temp;
}