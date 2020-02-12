#ifndef _FILTERS_H_
#define _FILTERS_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include "types.h"
    #include <math.h>

    #define RGB_COMPONENT_COLOR 255

    void colorChange(PPMImage *img, char color){
        if (img){
            if (color == 's'){
                for (int i = 0; i < img->x * img->y; i++){
                    img->data[i].green = img->data[i].red;
                    img->data[i].blue = img->data[i].red;
                }
            } else 
            if (color == 'r'){
                for (int i = 0; i < img->x * img->y; i++){
                    img->data[i].green = 0;
                    img->data[i].blue = 0;
                }
            } else 
            if (color == 'g'){
                for (int i = 0; i < img->x * img->y; i++){
                    img->data[i].red = 0;
                    img->data[i].blue = 0;
                }
            } else 
            if (color == 'b'){
                for (int i = 0; i < img->x * img->y; i++){
                    img->data[i].green = 0;
                    img->data[i].red = 0;
                }
            } else {
                printf("syntax error\n");
            }
        }
    }

    void negative(PPMImage *img){
        if (img){
            for (int i = 0; i < img->x * img->y; i++){
                img->data[i].red = RGB_COMPONENT_COLOR - img->data[i].red;
                img->data[i].green = RGB_COMPONENT_COLOR - img->data[i].green;
                img->data[i].blue = RGB_COMPONENT_COLOR - img->data[i].blue;
            }
        }
    }

    void thresholding(PPMImage *img, int threshold){
        if (img){
            for (int i = 0; i < img->x * img->y; i++){
                if (img->data[i].red > threshold){
                    img->data[i].red = RGB_COMPONENT_COLOR;
                } else {
                    img->data[i].red = 0;
                }

                if (img->data[i].green > threshold){
                    img->data[i].green = RGB_COMPONENT_COLOR;
                } else {
                    img->data[i].green = 0;
                }

                if (img->data[i].blue > threshold){
                    img->data[i].blue = RGB_COMPONENT_COLOR;
                } else {
                    img->data[i].blue = 0;
                }
            }
        }
    }

    void blackHalfThresholding(PPMImage *img, int threshold){
        if (img){
            for (int i = 0; i < img->x * img->y; i++){
                if (img->data[i].red > threshold){
                    img->data[i].red = 0;
                }

                if (img->data[i].green > threshold){
                    img->data[i].green = 0;
                }

                if (img->data[i].blue > threshold){
                    img->data[i].blue = 0;
                }
            }
        }
    }

    void whiteHalfThresholding(PPMImage *img, int threshold){
        if (img){
            for (int i = 0; i < img->x * img->y; i++){
                if (img->data[i].red > threshold){
                    img->data[i].red = RGB_COMPONENT_COLOR;
                }

                if (img->data[i].green > threshold){
                    img->data[i].green = RGB_COMPONENT_COLOR;
                }

                if (img->data[i].blue > threshold){
                    img->data[i].blue = RGB_COMPONENT_COLOR;
                }
            }
        }
    }

    void gammaCorrection(PPMImage *img, double gamma){
        if (img){
            for (int i = 0; i < img->x * img->y; i++){
                img->data[i].red = (pow(img->data[i].red, 1 / gamma)) / (pow(RGB_COMPONENT_COLOR, ((1 - gamma) / gamma)));
            }

            for (int i = 0; i < img->x * img->y; i++){
                img->data[i].green = (pow(img->data[i].green, 1 / gamma)) / (pow(RGB_COMPONENT_COLOR, ((1 - gamma) / gamma)));
            }

            for (int i = 0; i < img->x * img->y; i++){
                img->data[i].blue = (pow(img->data[i].blue, 1 / gamma)) / (pow(RGB_COMPONENT_COLOR, ((1 - gamma) / gamma)));
            }
        }
    }

    void levelChange(PPMImage *img, int black, int white){
        if (img){
            for (int i = 0; i < img->x * img->y; i++){
                if (img->data[i].red <= black){
                    img->data[i].red = 0;
                } else
                if (img->data[i].red >= white){
                    img->data[i].red = RGB_COMPONENT_COLOR;
                } else {
                    img->data[i].red = (img->data[i].red - black) * (RGB_COMPONENT_COLOR / (black - white));
                }

                if (img->data[i].green <= black){
                    img->data[i].green = 0;
                } else
                if (img->data[i].green >= white){
                    img->data[i].green = RGB_COMPONENT_COLOR;
                } else {
                    img->data[i].green = (img->data[i].green - black) * (RGB_COMPONENT_COLOR / (black - white));
                }

                if (img->data[i].blue <= black){
                    img->data[i].blue = 0;
                } else
                if (img->data[i].blue >= white){
                    img->data[i].blue = RGB_COMPONENT_COLOR;
                } else {
                    img->data[i].blue = (img->data[i].blue - black) * (RGB_COMPONENT_COLOR / (black - white));
                }
            }
        }
    }

    void contouring(PPMImage *img){
        if (img){
            for (int i = 0; i < img->x * img->y - img->x; i ++){
                img->data[i].red = abs(img->data[i + 1].red - img->data[i].red) + abs(img->data[i + img->x].red - img->data[i].red);
                img->data[i].green = abs(img->data[i + 1].green - img->data[i].green) + abs(img->data[i + img->x].green - img->data[i].green);
                img->data[i].blue = abs(img->data[i + 1].blue - img->data[i].blue) + abs(img->data[i + img->x].blue - img->data[i].blue);
            }
        }
    }     

    void verticalBlur(PPMImage *img){
        if (img){
            for (int i = 0; i < img->x * img->y - 1; i ++){
                img->data[i].red = (img->data[i].red / 2) +  (img->data[i + 1].red / 10); 
                img->data[i].green = (img->data[i].green / 2) + (img->data[i + 1].green / 10);
                img->data[i].blue = (img->data[i].blue / 2) + (img->data[i + 1].blue / 10);
            }
        }
    }

    void horizontalBlur(PPMImage *img){
        if (img){
            for (int i = img->x; i < img->x * img->y - img->x; i ++){
                img->data[i].red = (img->data[i].red / 2) +  (img->data[i + img->x].red / 10); 
                img->data[i].green = (img->data[i].green / 2) + (img->data[i + img->x].green / 10);
                img->data[i].blue = (img->data[i].blue / 2) + (img->data[i + img->x].blue / 10);
            }
        }
    }

    void histogramStretching(PPMImage *img){
        // find max and min
        localArgs *local;
        local->max[0].red = img->data[0].red;
        local->max[0].green = img->data[0].green;
        local->max[0].blue = img->data[0].blue; 
        
        local->min[0].red = img->data[0].red;
        local->min[0].green = img->data[0].green;
        local->min[0].blue = img->data[0].blue;

        for (int i = 1; i < img->x * img->y - 1; i ++){
            if (img->data[i].red > local->max[0].red){
                local->max[0].red = img->data[i].red;
            }
            if (img->data[i].green > local->max[0].green){
                local->max[0].green = img->data[i].green;
            }
            if (img->data[i].blue > local->max[0].blue){
                local->max[0].blue = img->data[i].blue;
            }

            if (img->data[i].red < local->min[0].red){
                local->min[0].red = img->data[i].red;
            }
            if (img->data[i].green < local->min[0].green){
                local->min[0].green = img->data[i].green;
            }
            if (img->data[i].blue < local->min[0].blue){
                local->min[0].blue = img->data[i].blue;
            }

        }
        
        if (img){
            for (int i = 0; i < img->x * img->y; i ++){
                img->data[i].red = (img->data[i].red - local->min[0].red) * (RGB_COMPONENT_COLOR / (local->max[0].red - local->min[0].red));
                img->data[i].green = (img->data[i].green - local->min[0].green) * (RGB_COMPONENT_COLOR / (local->max[0].green - local->min[0].green));
                img->data[i].blue = (img->data[i].blue - local->min[0].blue) * (RGB_COMPONENT_COLOR / (local->max[0].blue - local->min[0].blue));
            }
        }

        
    }

#endif