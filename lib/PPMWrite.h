#ifndef _PPMWRITE_H_
#define _PPMWRITE_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include "types.h"

    #define RGB_COMPONENT_COLOR 255

    void writePPM(const char *filename, PPMImage *img)
    {
        FILE *fp;
        //open file for output
        fp = fopen(filename, "wb");
        if (!fp) {
            fprintf(stderr, "Unable to open file '%s'\n", filename);
            exit(1);
        }

        //write the header file
        //image format
        fprintf(fp, "P6\n");
        
        //image size
        fprintf(fp, "%d %d\n",img->x,img->y);

        // rgb component depth
        fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);

        // pixel data
        fwrite(img->data, 3 * img->x, img->y, fp);
        fclose(fp);
    }

#endif