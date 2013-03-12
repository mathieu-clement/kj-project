/**
 * @file
 * 
 * @brief File containing the Main function for the presentation.
 */


#ifndef FIND_BARCODE_DD
#define FIND_BARCODE_DD

// Linear camera
#include "../HemLinCam.h" 

// Utilities to read and output pixels read on linear camera
#include "../simple_camera_reading.h"

// Set camera settings with TV remote control
#include "simple_camera_settings_with_tv_remote.h" 

// Basic functions such as sleep_ms()
#include "../basic_functions.h" 



// Utilities to read keys pressed on the TV remote control
#include "../tv_remote_utils.h" 

#define MY_THRESHOLD 240
#define DELTA 2


#define NOT_FOUND 0
#define ALL_WHITE -1
#define ALL_BLACK -2
#define TOO_MUCH_WHITE_LINES -3
#define NOT_ENOUGH_BLACK_LINES -4
#define WHITE_LINES_SUCK -5

//------------------
char* pixels;
signed int8 barcodeFound = 0;
unsigned int8 blackIndex = 0, whiteIndex = 0;
unsigned int16 white_lines[52], black_lines[52];
//------------------

void getLines(char* pixels);
void printStats();
int1 isSizeExpected( int8 expected, int8 value );
unsigned int8 diffBetween( int8 v1, int8 v2 );
signed int8 findBarcode();
signed int8 find_barcode(void);

#include "find_barcode.c"

#endif
