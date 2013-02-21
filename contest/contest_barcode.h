#ifndef CONTEST_BARCODE_H
#define CONTEST_BARCODE_H

int8 barcode_left_bound(unsigned char* pixels, int8 threshold);
int8 barcode_right_bound(unsigned char* pixels, int8 threshold);

/**
 * Barcodes such as specified in the description of the contest.
 * The value 1 is for a white stripe, and the value 0 is for a black stripe.
 */
int8 contest_barcodes[8][9] = {
    {}, // empty element in order to use the numbering of the document

                         // Barcode ID
    {0,0,1,1,0,1,1,0,0}, // 1
    {0,0,1,1,0,0,0,0,0}, // 2
    {0,0,0,0,0,1,1,0,0}, // 3
    {0,0,1,0,0,0,1,0,0}, // 4
    {0,0,0,1,0,1,0,0,0}, // 5
    {0,0,0,1,0,0,1,0,0}, // 6
    {0,0,1,0,0,1,0,0,0}  // 7
};

/**
 * Detect which barcode is matched by the camera (whose output is provided as argument).
 * 
 * @param pixels 102 pixels (3*34) as read by the linear camera
 * @param threshold above (and including) this value the pixel is considered white,
 *        otherwise it will be detected as black
 * @return barcode matching the pixels or -1 if there is no match.
 */
int8 detect_barcode(unsigned char* pixels, int8 threshold);

/**
 * Compare two arrays of int1[].
 * 
 * @param arr1 an array of int1[]
 * @param arr2 another array of int1[]. Must be as big as arr1.
 * @param size length of array
 * @return true (1) or (false) if arr1 has the same content as arr2.
 */
int1 compare_array(int1* arr1, int1* arr2, int8 size);

#include "contest_barcode.c"

#endif

