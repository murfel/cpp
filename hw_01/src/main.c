#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <../include/bmp.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: ./main crop-rotate <in-bmp> <out-bmp> <x> <y> <w> <h>\n");
        return 1;
    }

    if (strcmp(argv[1], "crop-rotate") == 0) {
        char ** data;
        BITMAPFILEHEADER file_header;
        BITMAPINFOHEADER dib_header;

        char ** new_data;
        BITMAPFILEHEADER new_file_header;
        BITMAPINFOHEADER new_dib_header;

        load_bmp(argv[2], &file_header, &dib_header, &data);
        crop(&file_header, &dib_header, &data, &new_file_header, &new_dib_header, &new_data, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));

        free(data[0]);
        free(data);

        rotate(&new_file_header, &new_dib_header, &new_data, &file_header, &dib_header, &data);
        save_bmp(argv[3], &file_header, &dib_header, &data);

        free(data[0]);
        free(data);
        free(new_data[0]);
        free(new_data);
    }
    else {
        printf("Unknown argument %s.\nUsage: ./main crop-rotate <in-bmp> <out-bmp> <x> <y> <w> <h>\n", argv[1]);
        return 1;
    }

    return 0;
}
