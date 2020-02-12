#ifndef _COMMANDS_H_
#define _COMMANDS_H_
    /* Lib for all command recognition*/
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <getopt.h>
    #include "PPMRead.h"
    #include "PPMWrite.h"
    #include "types.h"
    #include "filters.h"

    #define TRUE 1
    #define FALSE 0

    extern char *optarg;
    extern int optind, opterr, optopt;
    int opt;

    // read image file
    PPMImage *image;

    //option list
    static const char *optString = "i:o:dhkn34p:c:b:g:z:1:2:m:";

    static struct option long_options[] = {
        {"input",       required_argument, NULL, 'i'}, // -i  [path] {read file}
        {"output",      required_argument, NULL, 'o'}, // -o  [path] {write file}
        {"draw",        no_argument,       NULL, 'd'}, // -d         {draw img}
        {"change-color",required_argument, NULL, 'm'}, // -m  [color]{change color r, g, b, s}
        {"negative",    no_argument,       NULL, 'n'}, // -n         {negative}
        {"thresholding",required_argument, NULL, 'p'}, // -p  [num]  {thresholding}
        {"pc",          required_argument, NULL, '1'}, // -pc [num]  {black Half Thresholding 0-100}
        {"pb",          required_argument, NULL, '2'}, // -pb [num]  {white Half Thresholding 0-100}
        {"gamma",       required_argument, NULL, 'g'}, // -g  [num]  {gamma change 0.1-0.9}
        {"level-change",required_argument, NULL, 'z'}, 
        {"contouring",  no_argument,       NULL, 'k'},
        {"rx",          no_argument,       NULL, '3'},
        {"ry",          no_argument,       NULL, '4'},
        {"histogram",   no_argument,       NULL, 'h'},
        {NULL,          0,                 NULL,  0 }
    };

    /* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
    void wyswietl(char *n_pliku) {
        char polecenie[1024];      /* bufor pomocniczy do zestawienia polecenia */

        strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
        strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
        strcat(polecenie," &");
        printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
        system(polecenie);             /* wykonanie polecenia        */
        }

    void getOptional(int argc, char *argv[]){
        // while ((opt = getopt_long(argc, argv, optString, long_options, NULL )) != -1) { 
            while ((opt = getopt_long(argc, argv, optString, long_options, NULL)) != -1) { 
            switch(opt)
            {
                case 'i':
                    if (strlen(optarg) == 1 && optarg[0] == '-'){
                        globalArgs.inputFileName = "source/default.ppm";
                        // printf("input file name is: dafault\n");
                        image = readPPM(globalArgs.inputFileName);
                        globalArgs.isDraw = TRUE;
                    } else {
                        //check existing
                        if( access( optarg, F_OK ) != -1 ) {
                            globalArgs.inputFileName = optarg;
                            // printf("input file name is: %s\n", optarg);
                            image = readPPM(globalArgs.inputFileName);
                            globalArgs.isDraw = TRUE;
                        } else {
                            printf("file %s don't exist\n", optarg);
                            globalArgs.isDraw = FALSE;
                            exit(TRUE);
                        }
                    }
                    break;
                case 'o':
                    if (image){
                        if (strlen(optarg) == 1 && optarg[0] == '-'){
                            globalArgs.outFileName = "source/default.res.ppm";
                            // printf("out file name is: dafault\n");
                            writePPM(globalArgs.outFileName, image);
                        } else {
                            globalArgs.outFileName = optarg;
                            
                            // check extension 
                            char *ext = strrchr(optarg, '.');
                            if (!ext) { 
                                // if filename haven't extension, then appeng .pgm to end
                                strncat((char*)globalArgs.outFileName, ".ppm", 4);
                            }
                            writePPM(globalArgs.outFileName, image);
                            // printf("out file name is: %s\n", optarg);
                        }
                    } else {
                        printf("syntax error\n");
                    } 
                    break;
                case 'd':
                    if (globalArgs.isDraw){
                        if (globalArgs.isDraw != FALSE && globalArgs.inputFileName != NULL){
                            wyswietl((char*)globalArgs.inputFileName);
                            printf("draw file\n");
                        } else {
                            printf("syntax error\n");
                        }
                    }
                    break;
                case 'm':
                    if (strlen(optarg) == 1){
                        colorChange(image, optarg[0]); 
                    } else {
                        printf("syntax error\n");
                    } 
                    break;
                case 'n':
                    negative(image);
                    break;
                case 'p':
                    thresholding(image, atoi(optarg));
                    break;
                case '1':
                    blackHalfThresholding(image, atoi(optarg));
                    printf("pc\n");
                    break;
                case '2':
                    whiteHalfThresholding(image, atoi(optarg));
                    break;
                case 'g':
                    gammaCorrection(image, atof(optarg));
                    break;
                case 'z':
                    // read two arguments
                    optind--;
                    int pos = 0;
                    char* colors[2];
                    for( ;optind < argc && *argv[optind] != '-'; optind++){
                        colors[pos] = argv[optind];
                        pos += 1;
                    }
                    int white = atoi(colors[0]);
                    int black = atoi(colors[1]);

                    levelChange(image, white, black);
                    break;
                case 'k':
                    contouring(image);
                    break;
                case '3':
                    verticalBlur(image);
                    break;
                case '4':
                    horizontalBlur(image);
                    break;
                case 'h':
                    histogramStretching(image);
                    break;
                case ':':
                    printf("option needs a value\n");
                    printf("syntax:\n");
                    printf("./main.c [-i name] [-o name] [-d] [-n] [-r] [-p num] [--pc num] [--pb num] [-g num] [-z num1 num2] \n");
                    break;
                case '?':
                    printf("unknown option: %c\n", optopt);
                    printf("syntax:\n");
                    printf("./main.c [-i name] [-o name] [-d] [-n] [-r] [-p num] [--pc num] [--pb num] [-g num] [-z num1 num2] \n");
                    break;
                default:
                    printf("syntax:\n");
                    printf("./main.c [-i name] [-o name] [-d] [-n] [-r] [-p num] [--pc num] [--pb num] [-g num] [-z num1 num2] \n");
                    break;
            }
        }
    }

#endif