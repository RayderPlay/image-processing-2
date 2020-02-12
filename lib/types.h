#ifndef _TYPES_H_
#define _TYPES_H_

    struct globalArgs_t 
    {
        const char* inputFileName; // -i [input file name]
        const char* outFileName;   // -o [out file name]
        int isDraw;                // -d
        char* color;               // -m [color (r)ed, (g)reen, (b)lue, (s)gray converion]
    } globalArgs;

    typedef struct {
        unsigned char red,green,blue;
    } PPMPixel;

    typedef struct {
        int x, y;
        PPMPixel *data;
    } PPMImage;

    typedef struct
    {
        PPMPixel *min;
        PPMPixel *max;
    }localArgs;
    

#endif