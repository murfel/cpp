#ifndef __BMPH
#define __BMPH

#include <stdint.h>

// https://wiki.multimedia.cx/index.php?title=BMP

typedef struct BITMAPFILEHEADER {
 char magic[2];              // 'B' 'M'
 int32_t file_size;
 int16_t reserved[2];
 int32_t offset;            // offset to bitmap data, relative to start of file
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER {
 int32_t header_size;                // 40
 int32_t width;
 int32_t height;                     // if height > 0 then bitmap data is upside down (i.e. last scanline first)
                                     // else height = abs(height) and bitmap data is ordered normally
 int16_t planes;                     // 1
 int16_t bits_per_pixel;             // must be 0 (bpp is implied by embedded JPEG or PNG image), 1, 4, 8, 16, 24 or 32
 int32_t compression;                // 0 = uncompressed, 1 = RLE8, 2 = RLE4, 3 = bitfields, 4 = JPEG, 5 = PNG
 int32_t bitmap_data_size;
 int32_t hor_pixels_per_meter;
 int32_t vert_pixels_per_meter;
 int32_t number_of_colors;           // only relevant for bits_per_pixel < 16; if set to zero, it's assumed to be 2^bits_per_pixel
 int32_t number_of_important_colors; // 0 means all colors are important
} BITMAPINFOHEADER;


int load_bmp(const char *, BITMAPFILEHEADER *, BITMAPINFOHEADER *, char ***);
int crop(BITMAPFILEHEADER *, BITMAPINFOHEADER *, char ***, BITMAPFILEHEADER *, BITMAPINFOHEADER *, char ***, int, int, int, int);
int rotate(BITMAPFILEHEADER *, BITMAPINFOHEADER *, char ***, BITMAPFILEHEADER *, BITMAPINFOHEADER *, char ***);
int save_bmp(const char *, BITMAPFILEHEADER *, BITMAPINFOHEADER *, char ***);

#endif
