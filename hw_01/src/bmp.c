#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <../include/bmp.h>

#define BYTES_PER_PIXEL 3

typedef size_t (*file_io)(void *, size_t, size_t, FILE *);

static int calc_line_width(int width) {
    int line_width = width * 3;
    while (line_width % 4 != 0) {
        line_width++;
    }
    return line_width;
}

int load_bmp(const char * filename, BITMAPFILEHEADER * file_header, BITMAPINFOHEADER * dib_header, char *** data) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("Failed to open file\n");
        exit(1);
    }

    if (!fread(file_header, sizeof(BITMAPFILEHEADER), 1, fp)) exit(1);
    if (!fread(dib_header, sizeof(BITMAPINFOHEADER), 1, fp)) exit(1);

    int line_width = calc_line_width(dib_header->width);
    int line_width_no_padding = BYTES_PER_PIXEL * dib_header->width;
    int padding_len = line_width - line_width_no_padding;

    *data = malloc(dib_header->height * sizeof(char *));
    char * temp = malloc(dib_header->height * line_width_no_padding);
    if (!*data || !temp) {
        exit(1);
    }

    for (int i = 0; i < dib_header->height; i++) {
        (*data)[i] = temp + line_width_no_padding * i;
    }

    for (int i = dib_header->height - 1; i >= 0; i--) {
        if(!fread((*data)[i], 1, line_width_no_padding, fp)) exit(1);
        fseek(fp, padding_len, SEEK_CUR);
    }

    fclose(fp);

    return 0;
}

int save_bmp(const char * filename, BITMAPFILEHEADER * file_header, BITMAPINFOHEADER * dib_header, char *** data) {
    FILE * fp = fopen(filename, "wb");
    if (!fp) {
        printf("Failed to open file\n");
        exit(1);
    }

    if (!fwrite(file_header, sizeof(BITMAPFILEHEADER), 1, fp)) exit(1);
    if (!fwrite(dib_header, sizeof(BITMAPINFOHEADER), 1, fp)) exit(1);

    int line_width = calc_line_width(dib_header->width);
    int line_width_no_padding = BYTES_PER_PIXEL * dib_header->width;
    int padding_len = line_width - line_width_no_padding;

    printf("padding_len %d\n", padding_len);
    printf("line_width_no_padding %d\n", line_width_no_padding);

    int zero = 0;
    for (int i = dib_header->height - 1; i >= 0; i--) {
        if(!fwrite((*data)[i], 1, line_width_no_padding, fp)) exit(1);
        if(!fwrite(&zero, padding_len, 1, fp)) exit(1);
    }

    fclose(fp);

    return 0;
}

int crop(BITMAPFILEHEADER * file_header, BITMAPINFOHEADER * dib_header, char *** data, BITMAPFILEHEADER * new_file_header, BITMAPINFOHEADER * new_dib_header, char *** new_data, int x, int y, int width, int height) {
    int line_len_no_padding = BYTES_PER_PIXEL * width;

    *new_data = malloc(height * sizeof(char *));
    char * temp = malloc(height * line_len_no_padding);

    if (!*new_data || !temp) {
        exit(1);
    }

    for (int i = 0; i < height; i++) {
        (*new_data)[i] = temp + line_len_no_padding * i;
    }

    int x_offset = BYTES_PER_PIXEL * x;
    for (int i = 0; i < height; i++) {
        memcpy((*new_data)[i], (*data)[y + i] + x_offset, line_len_no_padding);
    }

    memcpy(new_file_header, file_header, sizeof(BITMAPFILEHEADER));
    memcpy(new_dib_header, dib_header, sizeof(BITMAPINFOHEADER));

    new_dib_header->height = height;
    new_dib_header->width = width;
    new_dib_header->bitmap_data_size = height * calc_line_width(width);

    new_file_header->file_size = new_file_header->offset + new_dib_header->bitmap_data_size;

    return 0;
}

int rotate(BITMAPFILEHEADER * file_header, BITMAPINFOHEADER * dib_header, char *** data, BITMAPFILEHEADER * new_file_header, BITMAPINFOHEADER * new_dib_header, char *** new_data) {
    int line_len_no_padding = BYTES_PER_PIXEL * dib_header->height;

    *new_data = malloc(dib_header->width * sizeof(char *));
    char * temp = malloc(dib_header->width * line_len_no_padding);

    if (!*new_data || !temp) {
        exit(1);
    }

    for (int i = 0; i < dib_header->width; i++) {
        (*new_data)[i] = temp + line_len_no_padding * i;
    }

    for (int i = 0; i < dib_header->height; i++) {
        for (int j = 0; j < dib_header->width; j++) {
            memcpy((*new_data)[j] + (dib_header->height - i - 1) * BYTES_PER_PIXEL, (*data)[i] + BYTES_PER_PIXEL * j, BYTES_PER_PIXEL);
        }
    }

    memcpy(new_file_header, file_header, sizeof(BITMAPFILEHEADER));
    memcpy(new_dib_header, dib_header, sizeof(BITMAPINFOHEADER));

    new_dib_header->height = dib_header->width;
    new_dib_header->width = dib_header->height;
    new_dib_header->bitmap_data_size = new_dib_header->height * calc_line_width(new_dib_header->width);

    new_file_header->file_size = new_file_header->offset + new_dib_header->bitmap_data_size;

    return 0;
}
