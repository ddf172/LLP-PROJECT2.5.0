#include "Headers/FileProcessing.h"
#include "Headers/Bitmap.h"

FILE *open_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File does not exist");
        return NULL;
    }
    return file;
}

bool read_file_prop(FILE *file, void *prop, size_t size, size_t number){
    if (file == NULL || prop == NULL){
        return false;
    }
    size_t temp = fread(prop, size, number, file);
    if (temp < 1){
        printf("INVALID FILE");
        return false;
    }
    return true;
}

bool read_file_header(FILE *file, BITMAPFILEHEADER *BMFH){
    if (file == NULL || BMFH == NULL){
        return false;
    }
    if (!read_file_prop(file, &BMFH->bfType, sizeof(BMFH->bfType), 1)){ return false;}
    if (!read_file_prop(file, &BMFH->bfSize, sizeof(BMFH->bfSize), 1)){ return false;}
    if (!read_file_prop(file, &BMFH->bfReserved1, sizeof(BMFH->bfReserved1), 1)){ return false;}
    if (!read_file_prop(file, &BMFH->bfReserved2, sizeof(BMFH->bfReserved2), 1)){ return false;}
    if (!read_file_prop(file, &BMFH->bfOffBits, sizeof(BMFH->bfOffBits), 1)){ return false;}
    return true;
}

bool read_info_header(FILE *file, BITMAPINFOHEADER *BMIH){
    if (file == NULL || BMIH == NULL){
        return false;
    }
    if (!read_file_prop(file, &BMIH->biSize, sizeof(BMIH->biSize),1 )){ return false;}
    if (!read_file_prop(file, &BMIH->biWidth, sizeof(BMIH->biWidth),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biHeight, sizeof(BMIH->biHeight),1 )){ return false;}
    if (!read_file_prop(file, &BMIH->biPlanes, sizeof(BMIH->biPlanes),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biBitCount, sizeof(BMIH->biBitCount),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biCompression, sizeof(BMIH->biCompression),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biSizeImage, sizeof(BMIH->biSizeImage),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biXPelsPerMeter, sizeof(BMIH->biXPelsPerMeter),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biYPelsPerMeter, sizeof(BMIH->biYPelsPerMeter),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biClrUsed, sizeof(BMIH->biClrUsed),1)){ return false;}
    if (!read_file_prop(file, &BMIH->biClrImportant, sizeof(BMIH->biClrImportant),1)){ return false;}
    return true;
}

bool read_pixels(FILE *file, BITMAPDATA *btd){
    if (file == NULL || btd == NULL){
        return false;
    }
    int row_size = ((btd->BMIH->biBitCount * btd->BMIH->biWidth + 31) / 32) * 4;
    unsigned char *buffer = malloc(row_size);
    if (buffer == NULL){
        return false;
    }
    fseek(file, btd->BMFH->bfOffBits, SEEK_SET);
    for (int i=0; i<btd->BMIH->biHeight; i++){
        if (fread(buffer, row_size, 1, file) != 1){
            free(buffer);
            return false;
        }

        for (int j=0; j<btd->BMIH->biWidth; j++){
            btd->pixels[i][j].B = buffer[j*3];
            btd->pixels[i][j].G = buffer[j*3+1];
            btd->pixels[i][j].R = buffer[j*3+2];
        }
        fseek(file, get_padding(btd->BMIH), SEEK_CUR);
    }
    free(buffer);
    return true;
}
FILE *create_file(char *filename) {
    if (filename == NULL) {
        return NULL;
    }
    if (fopen(filename, "r") != NULL) {
        printf("File already exists");
        return NULL;
    }
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("File creation error");
        return NULL;
    }
    return file;
}

bool write_bytes(FILE *file, unsigned char byte, size_t number) {
    if (file == NULL) {
        return false;
    }
    if (fwrite(&byte, sizeof(unsigned char), number, file) != 1) {
        return false;
    }
    return true;
}

bool write_headers(FILE *file, BITMAPFILEHEADER *BMFH, BITMAPINFOHEADER *BMIH){
    if (file == NULL || BMFH == NULL || BMIH == NULL){
        return false;
    }
    if (fwrite(&BMFH->bfType, sizeof(BMFH->bfType), 1, file) != 1) {return false;}
    if (fwrite(&BMFH->bfSize, sizeof(BMFH->bfSize), 1, file) != 1) {return false;}
    if (fwrite(&BMFH->bfReserved1, sizeof(BMFH->bfReserved1), 1, file) != 1) {return false;}
    if (fwrite(&BMFH->bfReserved2, sizeof(BMFH->bfReserved2), 1, file) != 1) {return false;}
    if (fwrite(&BMFH->bfOffBits, sizeof(BMFH->bfOffBits), 1, file) != 1) {return false;}
    if (fwrite(&BMIH->biSize, sizeof(BMIH->biSize), 1, file) != 1) {return false;}
    if (fwrite(&BMIH->biWidth, sizeof(BMIH->biWidth), 1, file) != 1) {return false;}
    if (fwrite(&BMIH->biHeight, sizeof(BMIH->biHeight), 1, file) != 1) {return false;}
    if (fwrite(&BMIH->biPlanes, sizeof(BMIH->biPlanes), 1, file) != 1) {return false;}
    if (fwrite(&BMIH->biBitCount, sizeof(BMIH->biBitCount), 1, file) != 1) {return false;}
    if (fwrite(&BMIH->biCompression, sizeof(BMIH->biCompression), 1, file) != 1) {return false;}
    if (fwrite(&BMIH->biSizeImage, sizeof(BMIH->biSizeImage), 1, file) != 1) {return false;}
    if (fwrite(&BMIH->biXPelsPerMeter, sizeof(BMIH->biXPelsPerMeter), 1, file) != 1) {return false;}
    if (fwrite(&BMIH->biYPelsPerMeter, sizeof(BMIH->biYPelsPerMeter), 1, file) != 1) {return false;}
    if (fwrite(&BMIH->biClrUsed, sizeof(BMIH->biClrUsed), 1, file) != 1) {return false;}
    if (fwrite(&BMIH->biClrImportant, sizeof(BMIH->biClrImportant), 1, file) != 1) {return false;}
    return true;
}

bool write_offset(FILE *file, unsigned int offset) {
    if (file == NULL) {
        return false;
    }
    const unsigned int headers_end = 54;
    if (fseek(file, headers_end+1, SEEK_SET) != 0) {
        return false;
    }
    unsigned int bytes_to_write = offset-(headers_end+1);
    for (int i = 0; i < bytes_to_write; i++) {
        if (!write_bytes(file, 0x00, 1)) {
            return false;
        }
    }
    return true;
}

bool write_pixels(FILE *file, PIXEL **pixels,unsigned int height,unsigned int width,unsigned int offset,unsigned int padding,unsigned int bit_count){
    if (file == NULL || pixels == NULL){
        return  false;
    }
    fseek(file, offset, SEEK_SET);
    int row_size = (((signed int) bit_count * (signed int) width + 31) / 32) * 4;
    unsigned char *buffer = malloc(sizeof(unsigned char) * row_size);
    if (buffer == NULL){
        return false;
    }
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            buffer[j*3] = pixels[i][j].B;
            buffer[j*3+1] = pixels[i][j].G;
            buffer[j*3+2] = pixels[i][j].R;
        }
        if (fwrite(buffer, row_size, 1, file) != 1){
            free(buffer);
            return false;
        }
        for (int j=0; j<padding; j++){
            if (!write_bytes(file, 0x00, 1)){
                free(buffer);
                return false;
            }
        }
    }
    free(buffer);
    return true;
}

bool write_to_file(FILE *file, BITMAPINFOHEADER *BMIH, BITMAPFILEHEADER *BMFH,  PIXEL **pixels){
    if (file == NULL || BMIH == NULL || BMFH == NULL || pixels == NULL){
        return false;
    }
    int padding = get_padding(BMIH);
    if (!write_headers(file, BMFH, BMIH)){
        return false;
    }
    if (!write_offset(file, BMFH->bfOffBits)){
        return false;}
    if (!write_pixels(file, pixels, BMIH->biHeight, BMIH->biWidth, BMFH->bfOffBits, padding, BMIH->biBitCount)){
        return false;
    }
    return true;
}

bool close_file(FILE *file) {
    if (fclose(file) != 0) {
        return false;
    }
    file = NULL;
    return true;
}
