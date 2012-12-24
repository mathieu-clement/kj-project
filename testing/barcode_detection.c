/*
    This is not meant to be run on the robot but on a regular computer.
*/

#include <stdio.h>

// Detect whether an array of pixels is a known barcode (5 black stripes)
int barcode_in_view(int* array)
{
    int black_lines = 0;

    int into_black_line = 0;

    // Iterate through array
    // if pixel is black: into_black_line = 1
    // if pixel is white: if into_black_line==1, then increment black_lines, into_black_lines=0

    int i=0;    
    for(i=0; i<102; i++)
    {
        printf("Pixel %3d: %3d. into_black_lines=%d, black_lines=%d\n", i, array[i],
                    into_black_line, black_lines);
        if(array[i] == 0)
        {
            into_black_line = 1;
        } else if(array[i] == 255) // else is not sufficient because we don't know how 
                                    // array is initialized
        {
            if(into_black_line)
            {
                black_lines++;
            }
            into_black_line = 0;
        }
    } // end for

    return black_lines >= 5;
}

int main(int argc, char ** argv)
{
    
    int array[] = {255,255,255,255,255,255,255,255,255,255,
                    0,0,0,0,0, 255,255,255,255,255, // 20 - 1st line of blacks
                   255,255,255,255,255,255,255,255,255,255, // 30
                    0,0,0,0,0,0,0,0,0,0, // 40 - 2nd line of blacks
                    255,255,255,255,255,255,255,255, // 48
                    0,0,0,0,0,0,0, // 55 - 3rd line of blacks
                   255,255,255,255,255, // 60
                    0,0,0,0, 255, 255, 255, 255, 255, 255, // 70 - 4th line of blacks
                    0,0,0,0,0,0,0, 255, 255, 255, // 80 - 5 th line of blacks
                   255,255,255,255,255,255,255,255,255,255, // 90
                   255,255,255,255,255,255,255,255,255,255, // 100
                   255, 255 // 102
     };

    printf("Barcode in view: %d\n", barcode_in_view(array));

    return 0;
}

