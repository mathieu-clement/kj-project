/**
 * @file
 * 
 * @brief Utilities to read and print pixels from the linear camera
 */

#ifndef SIMPLE_CAMERA_READING_H
#define SIMPLE_CAMERA_READING_H

// Aliases for arrays named by HemLinCam library
#define LEFT_PIXELS   HemLinCam_Pixels_Zone1
#define CENTER_PIXELS HemLinCam_Pixels_Zone2
#define RIGHT_PIXELS  HemLinCam_Pixels_Zone3

int1 cr_threshold_enabled = 0; ///< is camera threshold enabled?
int8 cr_threshold = 120; ///< default camera threshold
int8 cr_exposition_time = 1; ///< camera exposition time defaults to 1

void  cr_print_pixels(unsigned char *array34);
char* cr_make_single_pixels_array();
void  cr_print_pixels_bluetooth();

#include "simple_camera_reading.c"

#endif
