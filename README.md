# image-processing-2

Modify the image processing program from laboratory 3 according to the following assumptions:
-Selected program elements should create a module with an appropriate header file.
Enter the data structure describing the overall stored image. Use the ability to dynamically determine the size of arrays to match the size of stored data to the actual dimensions of the image. Modify the program functions to use the introduced structure.
-Complete the functions with assertions checking the proposed conditions of correctness.
-Add support for color images in ppm (P3) format to the program. The image loading function should automatically recognize the file type and adjust the amount of allocated memory, and the image structure should store information about what image we are dealing with.
-Define the conversion function to gray levels for color images: each point of the new image is the arithmetic mean of the color component values.
Replace user menu using program call arguments. The program should recognize the options selected from the following (indicated by the teacher):
    -i <filename> name of the file to read (if the '-' character is given instead of the name, the image should be read from the standard input instead of the file;
    -o <filename> name of the file to be saved (if the '-' character is given instead of the name, the image should be printed on the standard output instead of the file;
    -d image after processing should be displayed;
    -m <color> choose the color to process: r - red, g - green, b - blue, s - conversion to gray
  and additionally selected options related to the defined image processing functions:
  -n negative;
    -p <threshold> threshold with threshold value.
    -pc <threshold> threshold black with a threshold of a given value.
    -pb <threshold> threshold of white with a threshold of a given value.
    -g <coefficient> gamma correction with a coefficient of a given value.
    -z <czern> <biel> level change
    -k contouring;
    -rx horizontal blur;
    - vertical blurring;
    -h stretching the histogram;
    -s s12 s12 s13 s21 s22 s23 s31 s32 s33 weave;

The order in which the options may appear is optional. The -i option must appear when the program is invoked. Its absence, as well as the lack of file names after the -i, -o options, and the threshold value after -p should result in an appropriate error message. The absence of the -o option means output to the standard output. The program can use the appropriately modified function from the options.c file.
Modify the program documentation to match the changes made in the program.
